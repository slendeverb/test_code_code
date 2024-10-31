#include <iostream>
#include <vector>
#include <bitset>
#include <optional>

using Matrix = std::vector<std::vector<int>>;
using Vector = std::vector<int>;

const int n = 5;
const int m = 4;

bool lessThanOrEqual(const Vector& a,const Vector& b){
    for(int i=0;i<a.size();i++){
        if(a[i]>b[i]){
            return false;
        }
    }
    return true;
}

void workForward(Vector& work,const Vector& allocationi){
    for(int j=0;j<work.size();j++){
        work[j]+=allocationi[j];
    }
}

std::optional<Vector> isSafe(const Vector& available,const Matrix& need,const Matrix& allocation){
    Vector safe_sequence;
    Vector work{available};
    std::bitset<n> finish;
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            if(finish[i]==true||!lessThanOrEqual(need[i],work)){
                continue;
            }
            workForward(work,allocation[i]);
            finish[i]=true;
            safe_sequence.push_back(i);
        }
    }
    if(finish.all()){
        return std::optional<Vector>{safe_sequence};
    }else{
        return std::nullopt;
    }
}

bool canRequest(const int process_num,const Vector& requesti,const Vector& available,const Matrix& need){
    if(!lessThanOrEqual(requesti,need[process_num])){
        return false;
    }
    if(!lessThanOrEqual(requesti,available)){
        return false;
    }
    return true;
}

void attemptAlloc(const int process_num,const Vector& requesti,Vector& available,Matrix& allocation,Matrix& need){
    for(int j=0;j<requesti.size();j++){
        available[j]-=requesti[j];
        allocation[process_num][j]+=requesti[j];
        need[process_num][j]-=requesti[j];
    }
}

void undoAttemptAlloc(const int process_num,const Vector& requesti,Vector& available,Matrix& allocation,Matrix& need){
    for(int j=0;j<requesti.size();j++){
        available[j]+=requesti[j];
        allocation[process_num][j]-=requesti[j];
        need[process_num][j]+=requesti[j];
    }
}

int main(int argc, char** argv) {
    Vector available{1, 6, 2, 2};
    Matrix max;
    Matrix allocation{{0, 0, 3, 2}, {1, 0, 0, 0}, {1, 3, 5, 4}, {0, 3, 3, 2}, {0, 0, 1, 4}};
    Matrix need{{0, 0, 1, 2}, {1, 7, 5, 0}, {2, 3, 5, 6}, {0, 6, 5, 2}, {0, 6, 5, 6}};

    auto safe_sequence=isSafe(available,need,allocation);
    if(safe_sequence.has_value()){
        std::cout<<"Safe Sequence:\n";
        for(int i=0;i<safe_sequence.value().size();i++){
            std::cout<<safe_sequence.value()[i]<<" ";
        }
        std::cout<<"\n";
    }else{
        std::cout<<"System is not safe.\n";
    }

    std::cout<<"\n";
    int process_num=2;
    Vector requesei{1,2,2,2};
    if(canRequest(process_num,requesei,available,need)){
        attemptAlloc(process_num,requesei,available,allocation,need);
        if(isSafe(available,need,allocation).has_value()){
            std::cout<<"Safe Sequence:\n";
            for(int i=0;i<safe_sequence.value().size();i++){
                std::cout<<safe_sequence.value()[i]<<" ";
            }
            std::cout<<"\n";
        }else{
            std::cout<<"Process: "<<process_num<<"\n";
            std::cout<<"Request Failed.\n";
            std::cout<<"Request Sequence:\n";
            for(int i=0;i<requesei.size();i++){
                std::cout<<requesei[i]<<" ";
            }
            std::cout<<"\n";
            std::cout<<"System is not safe.\n";
            undoAttemptAlloc(process_num,requesei,available,allocation,need);
        }
    }else{
        std::cout<<"Process: "<<process_num<<"\n";
        std::cout<<"Request Failed.\n";
        std::cout<<"Request Sequence:\n";
        for(int i=0;i<requesei.size();i++){
            std::cout<<requesei[i]<<" ";
        }
        std::cout<<"\n";
        std::cout<<"Request can not be satisfied.\n";
    }
}