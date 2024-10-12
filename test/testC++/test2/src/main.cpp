// #include "header.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int duplicateNumbersXOR(vector<int>& nums) {
        long long mask = 0;
        int ans = 0;
        for (const auto& x : nums) {
            if ((mask >> x) & 1) {
                ans ^= x;
            } else {
                mask |= (1ll << x);
            }
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> nums{1, 2, 1, 3};
    std::cout << std::format("{}\n", Solution{}.duplicateNumbersXOR(nums));
}