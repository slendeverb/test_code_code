#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int w[1100][1100], ridge, valley, n;
bool vis[1100][1100], R, V;
queue<pair<int, int>> q;
int way[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

bool inboard(int x, int y)
{
    if (x < 1 || x > n || y < 1 || y > n)
    {
        return false;
    }
    return true;
}

void bfs(int x, int y)
{
    q.push({x, y});
    vis[x][y] = true;
    while (!q.empty())
    {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int i = 0; i < 8; i++)
        {
            int nx = x + way[i][0], ny = y + way[i][1];
            if (!inboard(nx, ny))
            {
                continue;
            }
            else if (w[x][y] != w[nx][ny])
            {
                if (w[x][y] < w[nx][ny])
                {
                    R = false;
                }
                else if (w[x][y] > w[nx][ny])
                {
                    V = false;
                }
            }
            else if (!vis[nx][ny] && w[x][y] == w[nx][ny])
            {
                q.push({nx, ny});
                vis[nx][ny] = true;
            }
        }
    }
    if (R && V)
    {
        ridge++;
        valley++;
    }
    else if (R || V)
    {
        if (R)
            ridge++;
        if (V)
            valley++;
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> w[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            R = V = true;
            if (!vis[i][j])
            {
                bfs(i, j);
            }
        }
    }
    cout << ridge << " " << valley << "\n";
    return 0;
}