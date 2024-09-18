// #include "header.h"
#include <bits/stdc++.h>

class Solution{
public:
    int latestTimeCatchTheBus(std::vector<int>& buses, std::vector<int>& passengers, int capacity){
        std::ranges::sort(buses);
        std::ranges::sort(passengers);
        int pos=0,space=0;
        size_t passengers_num=passengers.size();
        for(int arrive_time:buses){
            space=capacity;
            while(space>0&&pos<passengers_num&&passengers[pos]<=arrive_time){
                space--;
                pos++;
            }
        }

        pos--;
        int ans=space>0?buses.back():passengers[pos];
        while(pos>=0&&passengers[pos]==ans){
            pos--;
            ans--;
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> buses{10,20};
    std::vector<int> passengers{2,17,18,19};
    const int capacity=2;
    Solution so;
    std::cout<<"The latest time to catch the bus is: "<<so.latestTimeCatchTheBus(buses,passengers,capacity)<<std::endl;
}