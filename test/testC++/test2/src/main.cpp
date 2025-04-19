#include "header.h"
using namespace std;

class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long ans=0;
        std::unordered_map<int,int> cnt;
        int pairs=0,left=0;
        for(int x:nums){
            pairs+=cnt[x]++;
            while(pairs>=k){
                pairs-=--cnt[nums[left]];
                left++;
            }
            ans+=left;
        }
        return ans;
    }
};

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
}