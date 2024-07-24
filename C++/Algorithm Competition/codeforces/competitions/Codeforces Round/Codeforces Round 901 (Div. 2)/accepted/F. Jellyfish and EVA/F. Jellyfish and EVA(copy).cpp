#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 5e3 + 5;
int n = 5000, m = 0;
vector<vector<int>> G(N), Gx(N);
long double f[N], g[N][N];

bool cmp(int u, int v)
{
    return f[u] > f[v];
}

void init()
{
    for (int i = 1; i <= n; i += 2)
    {
        for (int j = 1; j <= i; j++)
        {
            g[i][j] = 1.00 / i;
        }
    }

    for (int i = 2; i <= n; i += 2)
    {
        g[i][1] = 1.00;
        for (int j = 1; j <= i; j++)
        {
            g[i][j] /= i;
        }
        if (i + 2 <= n)
        {
            for (int j = 1; j <= i; j++)
            {
                g[i + 2][j + 1] += g[i][j] * (i - j + 1);
                g[i + 2][j + 2] += g[i][j] * j;
            }
        }
    }
}

void init2()
{
    for (int u = 1; u <= n; u++)
    {
        f[u] = 0.00;
        G[u].clear(), Gx[u].clear();
    }
    n = m = 0;
}

void work(int u)
{
    if (u == n)
    {
        f[u] = 1.00;
        return;
    }
    sort(G[u].begin(), G[u].end(), cmp);
    int sz = G[u].size();
    for (int i = 0; i < sz; i++)
    {
        int v = G[u][i];
        f[u] += f[v] * g[sz][i + 1];
    }
}

void solve()
{
    init2();
    cin >> n >> m;
    for (int i = 1, u = 0, v = 0; i <= m; i++)
    {
        cin >> u >> v;
        if (u != n)
        {
            G[u].emplace_back(v);
            Gx[v].emplace_back(u);
        }
    }
    for (int u = n; u >= 1; u--)
    {
        work(u);
    }
    cout << fixed << setprecision(12) << f[1] << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    init();
    while (T--)
    {
        solve();
    }
    return 0;
}