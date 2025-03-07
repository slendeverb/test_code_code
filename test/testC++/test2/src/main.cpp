#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int beautifulSubsets(vector<int>& nums, int k) {
        int ans = -1;
        std::unordered_map<int, int> cnt;

        auto dfs = [&](this auto&& dfs, int i) -> void {
            if (i == nums.size()) {
                ans++;
                return;
            }
            dfs(i + 1);
            int x = nums[i];
            if (cnt[x - k] == 0 && cnt[x + k] == 0) {
                cnt[x]++;
                dfs(i + 1);
                cnt[x]--;
            }
        };

        dfs(0);
        return ans;
    }
};

int main() {
    std::vector<int> nums{2,4,6};
    std::cout<<Solution{}.beautifulSubsets(nums,2);
}