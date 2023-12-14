#include <iostream>
using namespace std;

const int MAXM = 1e5 + 5;
const int MAXSZ = 205;
int sz[MAXM], a[MAXSZ], b[MAXSZ], num[MAXSZ], d[MAXM];
int f[MAXSZ][MAXM], f2[MAXSZ][MAXSZ][MAXSZ];
bool vis[MAXSZ][MAXSZ][MAXSZ];

int DFS(int x, int l, int r)
{
    if (l > r)
    {
        return 0;
    }
    if (vis[x][l][r])
    {
        return f2[x][l][r];
    }
    vis[x][l][r] = 1;
    if (a[r] <= x)
    {
        f2[x][l][r] = max(f2[x][l][r], DFS(x - a[r], l, r - 1) + b[r]);
    }
    f2[x][l][r] = max(f2[x][l][r], DFS(x, l, r - 1));
    return f2[x][l][r];
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> sz[i];
    }
    for (int i = 1; i <= m; i++)
    {
        num[sz[i]]++;
        d[++d[0]] = sz[i];
    }
    m = d[0];

    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = i; k <= n; k++)
            {
                f[k][j] = max(f[k][j], DFS(d[j], i + 1, k) + f[i][j - 1]);
                ans = max(ans, f[k][j]);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}