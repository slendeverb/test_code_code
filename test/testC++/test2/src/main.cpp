// #include "header.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int distinctPrimeFactors(vector<int>& nums) {
        std::unordered_set<int> s;
        for (const auto& num : nums) {
            auto x{num};
            for (int i = 2; i * i <= num; i++) {
                if (x % i == 0) {
                    s.insert(i);
                    while (x % i == 0) {
                        x /= i;
                    }
                }
            }
            if (x > 1) {
                s.insert(x);
            }
        }
        return s.size();
    }
};

int main(int argc, char** argv) {}