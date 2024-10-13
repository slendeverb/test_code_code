// #include "header.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        std::vector<int> ans(nums.size(),-1);
        for(int i=0;i<nums.size();i++){
            int x=nums[i];
            int cnt=0;
            while(x){
                if(!(x&1)){
                    if(cnt<=0){
                        ans[i]=-1;
                    }else{
                        ans[i]=nums[i]&~(1<<(cnt-1));
                    }
                    break;
                }
                cnt++;
                x>>=1;
            }
            if(!x){
                ans[i]=nums[i]&~(1<<(cnt-1));
            }
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    
}