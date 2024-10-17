// #include "header.h"
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

class Solution {
   public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        std::vector<int> req(n, -1);
        req[0] = 0;
        for (auto& p : requirements) {
            req[p[0]] = p[1];
        }
        if (req[0]) {
            return 0;
        }

        int m = std::ranges::max(req);
        std::vector<std::vector<int>> memo(n, std::vector<int>(m + 1, -1));
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if (i == 0) {
                return 1;
            }
            int& res = memo[i][j];
            if (res != -1) {
                return res;
            }
            res = 0;
            if (int r = req[i - 1]; r >= 0) {
                if (j >= r && j - i <= r) {
                    res = dfs(dfs, i - 1, r);
                }
            } else {
                for (int k = 0; k <= std::min(i, j); k++) {
                    res = (res + dfs(dfs, i - 1, j - k)) % MOD;
                }
            }
            return res;
        };
        return dfs(dfs,n-1,req[n-1]);
    }
};

int main(int argc, char** argv) {
    auto start = std::chrono::system_clock::now();
    int n{3};
    std::vector<std::vector<int>> requirements{{2,2},{0,0}};
    auto obj=Solution{};
    auto ans=obj.numberOfPermutations(n,requirements);
    std::println("{}",ans);
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::format("{}\n", duration);
}