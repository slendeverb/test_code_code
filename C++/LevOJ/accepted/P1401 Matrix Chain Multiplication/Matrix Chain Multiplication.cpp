#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// 可以使用动态规划来解决这个问题。令 dp[i][j] 表示计算 Ai 到 Aj 的连乘所需的最少实数乘法次数。首先初始化 dp[i][i] = 0，因为一个矩阵不需要进行任何乘法操作。

// 接下来，遍历长度为 L 的子序列（从 2 到 n），在每个子序列中，遍历所有可能的分割点 k，并更新 dp[i][j] 的值。状态转移方程为：

// dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j])

// 其中 p[i] 是第 i 个矩阵的行数，p[j+1] 是第 j 个矩阵的列数。最终 dp[1][n] 就是所求的最优解。

// p[i - 1] * p[k] * p[j] 代表在当前分割点 k 的情况下，计算 Ai 到 Aj 的连乘所需的实数乘法次数。

// 这里，p[i - 1] 是矩阵 Ai 的行数，p[k] 是矩阵 Ak 的列数，p[j] 是矩阵 Aj 的列数。
//根据矩阵乘法的定义，计算 Ai 到 Ak 的连乘结果矩阵（假设为 M）和 Ak+1 到 Aj 的连乘结果矩阵（假设为 N）时，M 矩阵的大小是 p[i - 1] 行 × p[k] 列，N 矩阵的大小是 p[k] 行 × p[j] 列。为了计算 M 和 N 的乘积，需要进行 p[i - 1] * p[k] * p[j] 次实数乘法。

// 在动态规划的状态转移方程中，dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j]) 用于比较当前分割点 k 和之前的分割点，以找到使得连乘所需实数乘法次数最小的分割点。

// 在这道题中，分割点是指在计算一串矩阵的连乘时，将矩阵序列拆分成两个子序列的位置。通过选择不同的分割点，我们可以得到不同的矩阵相乘的顺序，从而影响实数乘法的总次数。

// 以三个矩阵 A1, A2 和 A3 为例，我们可以选择以下两种计算顺序：

// 1. 先计算 (A1A2)A3，此时分割点位于 A1 和 A2 之间。
// 2. 先计算 A1(A2A3)，此时分割点位于 A2 和 A3 之间。

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0);
    int n;
    while (cin >> n)
    {
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
        vector<int> p(n + 1);
        bool invalid = false;

        for (int i = 1; i <= n; ++i)
        {
            int former, latter;
            cin >> former >> latter;
            if (i > 1 && former != p[i - 1])
            {
                invalid = true;
            }
            p[i - 1] = former;
            p[i] = latter;
        }

        if (invalid)
        {
            cout << "invalid argument\n";
            continue;
        }

        for (int L = 2; L <= n; ++L)
        {
            for (int i = 1; i <= n - L + 1; ++i) // 尽管矩阵大小的信息是从 0 开始存储的，但我们可以通过调整动态规划数组的下标使其从 1 开始，以保持与矩阵编号的一致性
            {
                int j = i + L - 1; // j-i+1=L
                dp[i][j] = LLONG_MAX;
                for (int k = i; k < j; ++k)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j]);
                }
            }
        }

        cout << dp[1][n] << "\n";
    }
    return 0;
}
