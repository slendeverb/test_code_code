// #include "header.h"
#include <bits/stdc++.h>

class Solution{
public:
    int distanceBetweenBusStops(std::vector<int>& distance,int start,int destination){
        long long dis1=0,dis2=0;
        int size=distance.size();
        int start1=std::min(start,destination);
        int start2=start1+size;
        int dest=std::max(start,destination);
        for(int i=start1;i<dest;i++){
            dis1+=distance[i];
        }
        for(int i=dest;i<start2;i++){
            dis2+=distance[i%size];
        }
        return std::min(dis1,dis2);
    }
};

int main(int argc, char** argv) {
    std::vector<int> distance{7,10,1,12,11,14,5,0};
    Solution so;
    std::cout<<so.distanceBetweenBusStops(distance,7,2);
}