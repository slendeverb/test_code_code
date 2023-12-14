#include <iostream>
#include <string>
#include <set>
using namespace std;

int n;
string s;
const int N = 25;
bool vis[42][42];

struct cor
{
    int x, y;
    bool operator<(const cor &a) const
    {
        if (x == a.x)
        {
            return y < a.y;
        }
        return x < a.x;
    }
};

set<cor> ans;

void dfs(int x, int y, int pos)
{
    if (pos == n)
    {
        ans.insert({x - 20, y - 20});
        return;
    }

    char ch = s[pos];

    if (ch == 'L')
    {
        if (!vis[x - 1][y])
        {
            dfs(x, y, pos + 1);
            vis[x - 1][y] = 1;
            dfs(x - 1, y, pos + 1);
            if (x - 1 != 20 && y != 20)
                vis[x - 1][y] = 0;
        }
        else
        {
            dfs(x - 1, y, pos + 1);
        }
    }
    else if (ch == 'R')
    {
        if (!vis[x + 1][y])
        {
            dfs(x, y, pos + 1);
            vis[x + 1][y] = 1;
            dfs(x + 1, y, pos + 1);
            if (x + 1 != 20 && y != 20)
                vis[x + 1][y] = 0;
        }
        else
        {
            dfs(x + 1, y, pos + 1);
        }
    }
    else if (ch == 'U')
    {
        if (!vis[x][y + 1])
        {
            dfs(x, y, pos + 1);
            vis[x][y + 1] = 1;
            dfs(x, y + 1, pos + 1);
            if (x != 20 && y + 1 != 20)
                vis[x][y + 1] = 0;
        }
        else
        {
            dfs(x, y + 1, pos + 1);
        }
    }
    else if (ch == 'D')
    {
        if (!vis[x][y - 1])
        {
            dfs(x, y, pos + 1);
            vis[x][y - 1] = 1;
            dfs(x, y - 1, pos + 1);
            if (x != 20 && y - 1 != 20)
                vis[x][y - 1] = 0;
        }
        else
        {
            dfs(x, y - 1, pos + 1);
        }
    }
}

void solve()
{
    cin >> n >> s;
    vis[20][20] = 1;
    ans.insert({0, 0});
    dfs(20, 20, 0);
    cout << ans.size() << "\n";
    for (auto it : ans)
    {
        cout << it.x << " " << it.y << "\n";
    }
}

int main()
{
    solve();
    return 0;
}