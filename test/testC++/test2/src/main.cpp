#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>&& nums) {
        if(nums.size()==1){
            return nums[0];
        }
        long long l=0,r=nums.size()-1;
        while(l<=r){
        	long long mid=((r-l)>>1)+l;
        	if(nums[mid<<1]!=nums[(mid<<1)+1]){
        		r=mid-1;
			}else{
				l=mid+1;
			}
		}
		return nums[l<<1];
    }
};

int main(int argc, char** argv) {
    std::cout<<Solution{}.singleNonDuplicate({1,1,2});
}