#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

const int N = 3e5 + 5;
vector<int> g[N];
int path[N], vis[N];
long long sum = 0, ans = 1;

long long quickPow(long long a, long long b)
{
    a %= MOD;
    long long res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

void dfs(int pos, int fa)
{
    vis[pos] = 1;
    for (int i = 0; i < g[pos].size(); i++)
    {
        int to = g[pos][i];
        if (to == fa)
        {
            continue;
        }
        if (vis[to] == 0)
        {
            path[to] = pos;
            dfs(to, pos);
        }
        else if (vis[to] == 2)
        {
            continue;
        }
        else
        {
            int tmp = pos;
            int cnt = 1;
            while (tmp != to)
            {
                cnt++;
                tmp = path[tmp];
            }
            sum += cnt;
            ans = (ans * (quickPow(2, cnt) - 1)) % MOD;
        }
    }
    vis[pos] = 2;
}

void solve()
{
    int n, m;
    while (cin >> n >> m)
    {
        memset(vis, 0, sizeof(vis));
        memset(path, 0, sizeof(path));
        for (int i = 1; i <= n; i++)
        {
            g[i].clear();
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        sum = 0, ans = 1;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                dfs(i, 0);
            }
        }
        ans = (ans * quickPow(2, m - sum)) % MOD;
        cout << ans << "\n";
    }
}

int main()
{
    // ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}