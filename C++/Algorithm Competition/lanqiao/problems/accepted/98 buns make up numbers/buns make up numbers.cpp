// 这个是从一个简单dp问题演化而来的:
// 手里分别有无数张面额为x,y,Z元的纸币，请问凑出i元的方法有多少种:
// 动态规划表达:dp[i]，dp[i]表示凑出i元有多少种可能
// 实现: dp[i] = dp[i] + dp[i-x] + dp[i-y] + dp[i-z];
// 意为，当前如果要凑i元钱，凑出之前必然是
// i-x,i-y,i-z元中的其中一个，如果i-x,i-y,i-z中的任意一个能凑出来，dp[i]就可以凑出来

#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int M = 1e7;
int n;
int a[N];
int dp[M];

void solve() {
    cin >> n;
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ++dp[a[i]];
    }
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i - a[j] < 0) {
                continue;
            }
            dp[i] = dp[i - a[j]] + dp[i];
            if (dp[i] != 0) {
                break;
            }
        }
        if (dp[i] == 0) {
            ++ans;
        }
    }
    if (ans > 10000) {
        cout << "INF\n";
        return;
    }
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}