// #include "header.h"
#include <bits/stdc++.h>

class SeatManager{
    public:
        SeatManager(int n){
            for(int i=1;i<=n;i++){
                pq.emplace(i);
            }
        }
        
        int reserve(){
            int res=pq.top();
            pq.pop();
            return res;
        }
        
        void unreserve(int seatNumber){
            pq.push(seatNumber);
        }
    
    private:
        std::priority_queue<int,std::vector<int>,std::greater<>> pq;
};

int main(int argc,char** argv){
    
}