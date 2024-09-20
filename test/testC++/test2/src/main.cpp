#include "header.h"

class Solution {
   public:
    std::vector<int> getSneakyNumbers(std::vector<int>& nums){
        std::vector<int> count(nums.size()-2,0);
        std::vector<int> ans;
        for(const auto& x:nums){
            count[x]++;
            if(count[x]==2){
                ans.push_back(x);
            }
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> nums{0,0,1,1,2,3,4,5};
    auto ans=Solution{}.getSneakyNumbers(nums);
    std::println("nums: {}, {}",ans[0],ans[1]);
}