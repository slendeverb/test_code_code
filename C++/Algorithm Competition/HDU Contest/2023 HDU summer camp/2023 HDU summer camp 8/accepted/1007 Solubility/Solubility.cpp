#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, u, v, k;

int root[N];

void initset()
{
    for (int i = 0; i <= n; i++)
    {
        root[i] = i;
    }
}

int find(int x)
{
    return x == root[x] ? x : root[x] = find(root[x]);
}

bool merge(int x, int y)
{
    int dx = find(x);
    int dy = find(y);
    if (dx != dy)
    {
        root[dy] = dx;
        return true;
    }
    return false;
}

void solve()
{
    cin >> n >> m;
    initset();
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v;
        merge(u, v);
    }
    cin >> k;
    if (k == 1)
    {
        int x;
        cin >> x;
        cout << "YES\n";
    }
    else
    {
        int x, rt;
        cin >> x;
        rt = find(x);
        bool ok = 1;
        for (int i = 2; i <= k; i++)
        {
            cin >> x;
            if (ok)
            {
                if (find(x) != rt)
                {
                    ok = 0;
                }
            }
        }
        if (ok)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}