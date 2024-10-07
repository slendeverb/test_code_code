// #include "header.h"
#include <bits/stdc++.h>

class Solution {
   public:
    int minRefuelStops(int target,int startFuel,std::vector<std::vector<int>>& stations){
        stations.push_back({target,0});
        int ans=0;
        int pre_position=0;
        int cur_fuel=startFuel;
        std::priority_queue<int> fuel_heap;
        for(const auto& station:stations){
            int position=station[0];
            cur_fuel-=position-pre_position;
            while (!fuel_heap.empty()&&cur_fuel<0){
                cur_fuel+=fuel_heap.top();
                fuel_heap.pop();
                ans++;
            }
            if(cur_fuel<0){
                return -1;
            }
            fuel_heap.push(station[1]);
            pre_position=position;
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    int target{100};
    int startFuel{10};
    std::vector<std::vector<int>> stations{{10,60},{20,30},{30,30},{60,40}};
    std::cout<<std::format("{}\n",Solution{}.minRefuelStops(target,startFuel,stations));
}