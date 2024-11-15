#include <iostream>
#include <vector>
#include <queue>
#include <initializer_list>
#include <unordered_map>
#include <random>
#include <cassert>

const int PageSize=100;

struct Frame{
    int id=0;
    bool isAlloc=false;
    int length=PageSize;
    int startAddress;
};

struct Segment{
    int id=0;
    bool isAlloc=false;
    int length;
    int startAddress;
};

struct SegmentTableRegister{
    int TL=0;
    int startAddress=0;
}str;

struct TLB{
    int TLBSize{16};
    std::unordered_map<int,std::unordered_map<int,int>> TLB;
}tlb;

struct cmp{
    bool operator()(const Frame* a,const Frame* b){
        return a->id>b->id;
    }
};

std::vector<Frame> memory(4096);
std::priority_queue<Frame*,std::vector<Frame*>,cmp> pq;
std::random_device rd{};
std::mt19937_64 gen{rd()};
std::uniform_int_distribution<> distIsAlloc(0,1);

int init=[](){
    int startAddress=0;
    for(int i=0;i<memory.size();i++){
        memory[i].id=i;
        memory[i].isAlloc=distIsAlloc(gen);
        memory[i].startAddress=startAddress;
        startAddress+=memory[i].length;
        if(!memory[i].isAlloc){
            pq.push(&memory[i]);
        }
    }
    return 0;
}();

struct Process{
    Process(std::initializer_list<int> initList){
        int idSegment=0;
        for(const auto& x:initList){
            programSegment.push_back(x);
            int tmp=x;
            int idPage=0;
            while(tmp>0){
                if(!pq.empty()){
                    auto top=pq.top();
                    pq.pop();
                    top->isAlloc=true;
                    segmentTable[idSegment][idPage++]=top->id;
                }
                tmp-=PageSize;
            }
            idSegment++;
        }
        str.TL=segmentTable.size();
        str.startAddress=1;
        size_t minSize=std::min<size_t>(tlb.TLBSize,segmentTable.size());
        for(int i=0;i<minSize;i++){
            tlb.TLB[i]=segmentTable[i];
        }
    }
    ~Process(){
        for(const auto& [segment,pageTable]:segmentTable){
            for(const auto& [page,frame]:pageTable){
                memory[frame].isAlloc=false;
                pq.push(&memory[frame]);
            }
        }
    }

    std::vector<int> programSegment;
    std::unordered_map<int,std::unordered_map<int,int>> segmentTable;
};

int main(int argc, char** argv) {
    Process process{500,600,1000,1400,1700};
    std::cout<<"Allocated Memory Frame Number:\n";
    for(const auto& [segment,pageTable]:process.segmentTable){
        for(const auto& [page,frame]:pageTable){
            std::cout<<frame<<" ";
        }
        std::cout<<"\n";
    }
    int S=3,d=467;
    int P=d/PageSize,A=d%PageSize;
    assert(S<=str.TL);
    std::cout<<"Accessing Memory:\n";
    std::cout << memory[tlb.TLB.at(S).at(P)].startAddress + A << "\n";
}