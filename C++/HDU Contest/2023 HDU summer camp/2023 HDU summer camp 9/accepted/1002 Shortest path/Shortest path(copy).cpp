#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
typedef long long LL;
#define ll LL
#define endl "\n"

const int N = 1e6;
ll n;
int f[N];

unordered_map<ll, int> mp;

void init()
{
    fill(f + 2, f + N, N);
    for (int i = 1; i < N; i++)
    {
        if (i * 2 < N)
        {
            f[i * 2] = min(f[i * 2], f[i] + 1);
        }
        if (i * 3 < N)
        {
            f[i * 3] = min(f[i * 3], f[i] + 1);
        }
        if (i + 1 < N)
        {
            f[i + 1] = min(f[i + 1], f[i] + 1);
        }
    }
}

ll dfs(ll n)
{
    if (n < N)
    {
        return f[n];
    }
    if (mp.count(n))
    {
        return mp[n];
    }
    return mp[n] = min(dfs(n / 2) + n % 2 + 1, dfs(n / 3) + n % 3 + 1);
}

void solve()
{
    cin >> n;
    cout << dfs(n) << endl;
}

signed main()
{
    // IOS;
    int T = 1;
    cin >> T;
    init();
    while (T--)
    {
        solve();
    }
    return 0;
}