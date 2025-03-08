#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        int n=flowers.size();
        
        long long leftFlowers=newFlowers-1LL*target*n;
        for(auto& flower:flowers){
            flower=std::min(flower,target);
            leftFlowers+=flower;
        }

        if(leftFlowers==newFlowers){
            return 1LL*n*full;
        }

        if(leftFlowers>=0){
            return std::max(1LL*(target-1)*partial+1LL*(n-1)*full,1LL*n*full);
        }

        std::ranges::sort(flowers);

        long long ans=0,preSum=0;
        int j=0;
        for(int i=1;i<=n;i++){
            leftFlowers+=target-flowers[i-1];
            if(leftFlowers<0){
                continue;
            }

            while(j<i&&1LL*flowers[j]*j<=preSum+leftFlowers){
                preSum+=flowers[j];
                j++;
            }

            long avg=(leftFlowers+preSum)/j;
            long long totalBeauty=avg*partial+1LL*(n-i)*full;
            ans=std::max(ans,totalBeauty);
        }
        return ans;
    }
};

int main() {
    std::vector<int> flowers{2, 4, 5, 3};
    long long newFlowers=10;
    int target=5;
    int full=2;
    int partial=6;
    std::println("total beauty:{}",Solution{}.maximumBeauty(flowers,newFlowers,target,full,partial));
}