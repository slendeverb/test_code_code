#include "header.h"
using namespace std;

class Solution {
    static constexpr int DIRS[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

   public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        std::vector memo(n, std::vector<std::array<int, 4>>(m));

        auto dfs = [&](this auto&& dfs, int i, int j, int k, bool rotated, int target) -> int {
            i += DIRS[k][0];
            j += DIRS[k][1];

            if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] != target) {
                return 0;
            }
            if (rotated && memo[i][j][k]) {
                return memo[i][j][k];
            }

            int res = dfs(i, j, k, rotated, 2 - target) + 1;
            if (rotated) {
                return memo[i][j][k] = res;
            }

            int maxs[4] = {n - i, j + 1, i + 1, m - j};
            k = (k + 1) % 4;
            if (std::min(maxs[k], maxs[(k + 3) % 4]) > res) {
                res = std::max(res, dfs(i, j, k, true, 2 - target) + 1);
            }
            return res;
        };

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 1) {
                    continue;
                }

                int maxs[4] = {n - i, j + 1, i + 1, m - j};
                for (int k = 0; k < 4; k++) {
                    if (maxs[k] > ans) {
                        ans = std::max(ans, dfs(i, j, k, false, 2) + 1);
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
    std::vector<std::vector<int>> grid{
        {2, 2, 1, 2, 2}, {2, 0, 2, 2, 0}, {2, 0, 1, 1, 0}, {1, 0, 2, 2, 2}, {2, 0, 0, 2, 2}};
    auto result = Solution{}.lenOfVDiagonal(grid);
    std::print("{}\n",result);
}