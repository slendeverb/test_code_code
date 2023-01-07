#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int n, k;
char v[2][N];
bool vis[2][N];

bool dfs(int x, int y, int water)
{
    if (y > n)
    {
        return true;
    }
    if (water >= y || v[x][y] == 'X' || vis[x][y])
    {
        return false;
    }
    vis[x][y] = true;
    bool tmp = dfs(!x, y + k, water + 1);
    if (tmp)
        return true;
    tmp = dfs(x, y + 1, water + 1);
    if (tmp)
        return true;
    tmp = dfs(x, y - 1, water + 1);
    if (tmp)
        return true;
    return tmp;
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < 2; i++)
    {
        cin >> v[i] + 1;
    }
    if (dfs(0, 1, 0))
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