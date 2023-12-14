#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
vector<int> g[N];

void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int sz = g[i].size();
        if (sz < 3)
        {
            ans++;
        }
        else if (sz > 3)
        {
            ans = 0;
            break;
        }
    }
    cout << ans << "\n";
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}