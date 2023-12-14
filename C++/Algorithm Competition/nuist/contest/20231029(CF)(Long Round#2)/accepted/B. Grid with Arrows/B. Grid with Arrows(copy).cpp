#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 1e5 + 5;
int n, m;

class Dsu
{
public:
    Dsu()
    {
        for (int i = 1; i <= N; i++)
        {
            root[i] = i;
        }
    }
    int find(int x)
    {
        return x == root[x] ? x : root[x] = find(root[x]);
    }
    void merge(int x, int y)
    {
        int dx = find(x);
        int dy = find(y);
        if (dx != dy)
        {
            root[dy] = dx;
        }
    }

private:
    int root[N];
};

void solve()
{
    cin >> n >> m;
    vector<vector<int>> ind(n + 1, vector<int>(m + 1, 0));
    vector<vector<char>> arrow(n + 1, vector<char>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> arrow[i][j];
        }
    }
    Dsu dsu;
    int x;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> x;
            if (arrow[i][j] == 'u')
            {
                if (i - x >= 1)
                {
                    ind[i - x][j]++;
                    dsu.merge((i - 1) * m + j, (i - 1 - x) * m + j);
                }
            }
            else if (arrow[i][j] == 'd')
            {
                if (i + x <= n)
                {
                    ind[i + x][j]++;
                    dsu.merge((i - 1) * m + j, (i - 1 + x) * m + j);
                }
            }
            else if (arrow[i][j] == 'l')
            {
                if (j - x >= 1)
                {
                    ind[i][j - x]++;
                    dsu.merge((i - 1) * m + j, (i - 1) * m + j - x);
                }
            }
            else if (arrow[i][j] == 'r')
            {
                if (j + x <= m)
                {
                    ind[i][j + x]++;
                    dsu.merge((i - 1) * m + j, (i - 1) * m + j + x);
                }
            }
        }
    }

    int cntInd0 = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (ind[i][j] == 0)
            {
                cntInd0++;
            }
            if (cntInd0 == 2)
            {
                break;
            }
        }
    }
    int total = n * m, canTickEveryCell = 1;
    for (int i = 2; i <= total; i++)
    {
        if (dsu.find(i) != dsu.find(i - 1))
        {
            canTickEveryCell = 0;
            break;
        }
    }
    if ((cntInd0 == 0 || cntInd0 == 1) && canTickEveryCell == 1)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
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