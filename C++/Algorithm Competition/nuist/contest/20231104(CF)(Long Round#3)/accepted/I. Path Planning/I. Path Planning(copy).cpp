#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define endl "\n"

const int N = 1e6 + 5;
int n, m;

bool check(int mid, vector<vector<int>> &grid)
{
    int last = -1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (grid[i][j] < mid)
            {
                if (last > j)
                {
                    return false;
                }
                last = j;
            }
        }
    }
    return true;
}

void solve()
{
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> grid[i][j];
        }
    }

    int l = 0, r = n * m;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (check(mid, grid))
        {
            l = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    cout << l << endl;
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