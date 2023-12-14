#include <bits/stdc++.h>
using namespace std;

#define int long long

int t, n, m;

const int N = 3e5 + 10;
int x[N];
int dp[N];
void solve()
{
    int a, b;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    dp[1] = b * x[1];
    for (int i = 2; i <= n; i++)
    {
        dp[i] = min(dp[i - 2] + b * (x[i] - x[i - 2]), dp[i - 2] + a * (x[i - 1] - x[i - 2]) + b * (x[i] - x[i - 1]));
    }
    cout << dp[n] << "\n";
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}