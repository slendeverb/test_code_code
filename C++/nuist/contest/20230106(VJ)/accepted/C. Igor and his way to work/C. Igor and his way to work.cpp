#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int n, m;
string s;
vector<string> v;
bool vis[1100][1100][4][3];
int way[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

typedef struct Q
{
    int x;
    int y;
    int dir;
    int left_turn;
} Q;

bool inboard(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return false;
    else
        return true;
}

bool bfs(int x1, int y1, int x2, int y2)
{
    queue<Q> q;
    for (int i = 0; i < 4; i++)
    {
        int nx = x1 + way[i][0];
        int ny = y1 + way[i][1];
        if (inboard(nx, ny) && v[nx][ny] != '*')
        {
            q.push({nx, ny, i, 2});
            vis[nx][ny][i][2] = true;
        }
    }
    while (!q.empty())
    {
        Q tmp = q.front();
        if (tmp.x == x2 && tmp.y == y2)
        {
            return true;
        }
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = tmp.x + way[i][0];
            int ny = tmp.y + way[i][1];
            if (inboard(nx, ny) && v[nx][ny] != '*')
            {
                if (tmp.dir == i)
                {
                    if (!vis[nx][ny][i][tmp.left_turn])
                    {
                        q.push({nx, ny, i, tmp.left_turn});
                        vis[nx][ny][i][tmp.left_turn] = true;
                    }
                }
                else if (tmp.left_turn > 0)
                {
                    if (!vis[nx][ny][i][tmp.left_turn - 1])
                    {
                        q.push({nx, ny, i, tmp.left_turn - 1});
                        vis[nx][ny][i][tmp.left_turn - 1] = true;
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    cin >> n >> m;
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        v.push_back(s);
        for (int j = 0; j < m; j++)
        {
            if (v[i][j] == 'S')
            {
                x1 = i, y1 = j;
            }
            if (v[i][j] == 'T')
            {
                x2 = i, y2 = j;
            }
        }
    }
    if (bfs(x1, y1, x2, y2))
    {
        cout << "YES"
             << "\n";
    }
    else
    {
        cout << "NO"
             << "\n";
    }
    return 0;
}