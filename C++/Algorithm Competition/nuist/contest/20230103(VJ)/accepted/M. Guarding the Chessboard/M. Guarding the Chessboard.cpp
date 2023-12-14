#include <iostream>
using namespace std;

int n, m, cnt, ans;
bool mark[15][15], vis[4][50];

bool check_cover()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mark[i][j] && !(vis[0][i] || vis[1][j] || vis[2][i + j] || vis[3][i - j + n]))
            {
                return false;
            }
        }
    }
    return true;
}

bool dfs(int ret, int pos)
{
    if (pos == ans)
    {
        return check_cover();
    }
    for (int i = ret; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (vis[0][i] && vis[1][j] && vis[2][i + j] && vis[3][i - j + n])
            {
                continue;
            }
            bool tmp[4] = {0};
            tmp[0] = vis[0][i], tmp[1] = vis[1][j], tmp[2] = vis[2][i + j], tmp[3] = vis[3][i - j + n];
            vis[0][i] = vis[1][j] = vis[2][i + j] = vis[3][i - j + n] = true;
            if (dfs(i, pos + 1))
            {
                vis[0][i] = tmp[0], vis[1][j] = tmp[1], vis[2][i + j] = tmp[2], vis[3][i - j + n] = tmp[3];
                return true;
            }
            vis[0][i] = tmp[0], vis[1][j] = tmp[1], vis[2][i + j] = tmp[2], vis[3][i - j + n] = tmp[3];
        }
    }
    return false;
}

int main()
{
    cin >> n;
    while (n)
    {
        cin >> m;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                char x;
                cin >> x;
                if (x == 'X')
                {
                    mark[i][j] = true;
                }
                else
                {
                    mark[i][j] = false;
                }
            }
        }
        ans = 0;
        while (!dfs(0, 0))
        {
            ans++;
        }
        printf("Case %d: %d\n", ++cnt, ans);
        cin >> n;
    }
    return 0;
}