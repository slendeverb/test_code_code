#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m, v, q, ret;
string s, q1;
vector<string> v1;
int way[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

bool move_judgecrash(int &x, int &y)
{
    for (int i = 0; i < v; i++)
    {
        if (ret == 0 || ret == 2 || ret == 4 || ret == 6)
        {
            int nx = x + way[ret][0];
            int ny = y + way[ret][1];
            if ((nx < 0 || nx >= n || ny < 0 || ny >= m) || v1[nx][ny] == '#')
            {
                v = 0;
                return true;
            }
            else
            {
                x = nx, y = ny;
            }
        }
        else
        {
            int nx = x + way[ret][0];
            int ny = y + way[ret][1];
            if ((nx < 0 || nx >= n || ny < 0 || ny >= m) || v1[nx][ny] == '#')
            {
                v = 0;
                return true;
            }
            else if (v1[x + way[ret][0]][y] == '#' && v1[x][y + way[ret][1]] == '#')
            {
                v = 0;
                return true;
            }
            else
            {
                x = nx, y = ny;
            }
        }
    }
    return false;
}

void change(int i)
{
    if (q1[i] == 'L')
    {
        ret--;
        if (ret < 0)
        {
            ret += 8;
        }
    }
    else if (q1[i] == 'R')
    {
        ret++;
        if (ret >= 8)
        {
            ret %= 8;
        }
    }
    else if (q1[i] == 'U')
    {
        v = v + 1;
    }
    else if (q1[i] == 'D')
    {
        v = max(0, v - 1);
    }
}

int main()
{
    cin >> n >> m;
    int x, y;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        v1.push_back(s);
        for (int j = 0; j < m; j++)
        {
            if (v1[i][j] == '*')
            {
                x = i, y = j;
            }
        }
    }
    cin >> q >> q1;
    for (int i = 0; i < q; i++)
    {
        change(i);
        if (move_judgecrash(x, y))
        {
            cout << "Crash! ";
        }
        cout << x + 1 << " " << y + 1 << "\n";
    }
    return 0;
}