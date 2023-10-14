// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

#define int long long

const int N = 2e5 + 5;
const int M = 55;
int n, m, q;
int t[N], dp[N];

struct node
{
    int k, s;
} fitnessPlan[M];

void solve()
{
    cin >> n >> m >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> t[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> fitnessPlan[i].k >> fitnessPlan[i].s;
        fitnessPlan[i].k = (1 << fitnessPlan[i].k);
    }
    int sum = 0;
    int pos = 1;
    for (int i = 1; i <= q; i++)
    {
        int time = t[i] - pos;
        memset(dp, 0, sizeof(dp));
        for (int p = 1; p <= m; p++)
        {
            for (int j = fitnessPlan[p].k; j <= time; j++)
            {
                dp[j] = max(dp[j], dp[j - fitnessPlan[p].k] + fitnessPlan[p].s);
            }
        }
        sum += dp[time];
        pos = t[i] + 1;
    }
    if (pos != n + 1)
    {
        int time = n - pos + 1;
        memset(dp, 0, sizeof(dp));
        for (int p = 1; p <= m; p++)
        {
            for (int j = fitnessPlan[p].k; j <= time; j++)
            {
                dp[j] = max(dp[j], dp[j - fitnessPlan[p].k] + fitnessPlan[p].s);
            }
        }
        sum += dp[time];
    }
    cout << sum << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}