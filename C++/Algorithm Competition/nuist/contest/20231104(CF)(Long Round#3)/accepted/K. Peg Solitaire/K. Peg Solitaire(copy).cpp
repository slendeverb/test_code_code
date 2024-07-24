#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

int n, m, k;
int ans;

void dfs(int cnt, vector<vector<int>> &grid)
{
    ans = min(ans, cnt);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (!grid[i][j])
            {
                continue;
            }
            if (i >= 3 && grid[i - 1][j] && !grid[i - 2][j])
            {
                grid[i][j] = 0;
                grid[i - 1][j] = 0;
                grid[i - 2][j] = 1;

                dfs(cnt - 1, grid);

                grid[i][j] = 1;
                grid[i - 1][j] = 1;
                grid[i - 2][j] = 0;
            }
            else if (i <= n - 2 && grid[i + 1][j] && !grid[i + 2][j])
            {
                grid[i][j] = 0;
                grid[i + 1][j] = 0;
                grid[i + 2][j] = 1;

                dfs(cnt - 1, grid);

                grid[i][j] = 1;
                grid[i + 1][j] = 1;
                grid[i + 2][j] = 0;
            }
            else if (j >= 3 && grid[i][j - 1] && !grid[i][j - 2])
            {
                grid[i][j] = 0;
                grid[i][j - 1] = 0;
                grid[i][j - 2] = 1;

                dfs(cnt - 1, grid);

                grid[i][j] = 1;
                grid[i][j - 1] = 1;
                grid[i][j - 2] = 0;
            }
            else if (j <= m - 2 && grid[i][j + 1] && !grid[i][j + 2])
            {
                grid[i][j] = 0;
                grid[i][j + 1] = 0;
                grid[i][j + 2] = 1;

                dfs(cnt - 1, grid);

                grid[i][j] = 1;
                grid[i][j + 1] = 1;
                grid[i][j + 2] = 0;
            }
        }
    }
}

void solve()
{
    cin >> n >> m >> k;
    ans = k;
    vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));
    int x, y;
    for (int i = 1; i <= k; i++)
    {
        cin >> x >> y;
        grid[x][y] = 1;
    }
    dfs(k, grid);
    cout << ans << endl;
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    FILE *in = freopen("./test/in.txt", "r", stdin), *out = freopen("./test/out.txt", "w", stdout);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}