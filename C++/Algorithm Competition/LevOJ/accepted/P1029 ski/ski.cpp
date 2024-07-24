#include <iostream>
using namespace std;

int n, m;
int a[110][110];

int dp[110][110];

int way[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool inboard(int x, int y)
{
    if (x < 1 || x > n || y < 1 || y > m)
    {
        return false;
    }
    return true;
}

int dfs(int x, int y)
{
    if (dp[x][y])
    {
        return dp[x][y];
    }

    int ans = 1;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + way[i][0];
        int ny = y + way[i][1];
        if (inboard(nx, ny) && a[x][y] > a[nx][ny])
        {
            ans = max(ans, dfs(nx, ny) + 1);
        }
    }
    dp[x][y] = ans;

    return ans;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ans = max(ans, dfs(i, j));
        }
    }
    cout << ans << "\n";
    return 0;
}