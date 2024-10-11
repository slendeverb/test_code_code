// #include "header.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        long long ans=0;
        std::unordered_map<int,int> cnt;
        for(int x:nums1){
            if(x%k){
                continue;
            }
            x/=k;
            for(int d=1;d*d<=x;d++){
                if(x%d){
                    continue;
                }
                cnt[d]++;
                if(d*d<x){
                    cnt[x/d]++;
                }
            }
        }
        for(int x:nums2){
            ans+=cnt.contains(x)?cnt[x]:0;
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> nums1{1,2,4,12};
    std::vector<int> nums2{2,4};
    int k{3};
    std::cout<<std::format("{}\n",Solution{}.numberOfPairs(nums1,nums2,k));
}