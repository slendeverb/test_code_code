#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int N = 1e6 + 10;
int t, n, m;
vector<string> v;
vector<int> a[N];
string s;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool judge(int x, int y)
{
    int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m)
        {
            continue;
        }
        if (v[nx][ny] == '.')
        {
            cnt++;
        }
    }
    if (cnt < 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void bfs(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    a[x][y] = 1;
    while (!q.empty())
    {
        int tmpx = q.front().first;
        int tmpy = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = tmpx + dx[i], ny = tmpy + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            {
                continue;
            }
            if (a[nx][ny] == 1)
            {
                continue;
            }
            if (v[nx][ny] == '.')
            {
                if (judge(nx, ny))
                {
                    v[nx][ny] = '+';
                    a[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
    }
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        int x = -1, y = -1;
        for (int i = 0; i < n; i++)
        {
            a[i].assign(m, 0);
            cin >> s;
            v.push_back(s);
            for (int j = 0; j < m; j++)
            {
                if (s[j] == 'L')
                {
                    x = i, y = j;
                }
            }
        }
        if (x != -1)
        {
            bfs(x, y);
        }
        for (vector<string>::iterator it = v.begin(); it != v.end(); it++)
        {
            cout << *it << "\n";
        }
        v.clear();
        for (int i = 0; i < n; i++)
        {
            a[i].clear();
        }
    }
    return 0;
}