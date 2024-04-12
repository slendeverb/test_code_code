#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int M = 1e5 + 5;
int n;
int a[N];
long long sum = 0;
long long ans = 0;
int dp[N][M];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum += a[i];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= sum; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (dp[i][j] == 0) {
                if (j == a[i]) {
                    dp[i][j] = 1;
                }
                if (dp[i - 1][j + a[i]] == 1) {
                    dp[i][j] = 1;
                }
                if (dp[i - 1][abs(j - a[i])] == 1) {
                    dp[i][j] = 1;
                }
            }
        }
    }

    for (int j = 1; j <= sum; ++j) {
        if (dp[n][j] == 1) {
            ++ans;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    solve();
    cout.flush();
    return 0;
}