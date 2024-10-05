// #include "header.h"
#include <bits/stdc++.h>

class Solution {
   public:
    int canCompleteCircuit(std::vector<int>& gas,std::vector<int>& cost){
        std::vector<int> sub(gas.size());
        int sum=0;
        int pre_sum=0;
        int ans=0;
        for(int i=0;i<gas.size();i++){
            sub[i]=gas[i]-cost[i];
            sum+=sub[i];
        }
        if(sum<0){
            return -1;
        }
        for(int i=0;i<sub.size();i++){
            if(!pre_sum&&sub[i]>0){
                ans=i;
            }
            pre_sum+=sub[i];
            if(pre_sum<0){
                pre_sum=0;
            }
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> gas{1,2,3,4,5};
    std::vector<int> cost{3,4,5,1,2};
    std::cout<<std::format("{}\n",Solution{}.canCompleteCircuit(gas,cost));
}