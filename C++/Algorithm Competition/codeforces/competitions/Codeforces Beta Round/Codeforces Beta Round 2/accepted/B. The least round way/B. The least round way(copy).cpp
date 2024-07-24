// #include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <utility>
using namespace std;

// #define int long long
#define endl "\n"

const int N = 1005;
int n;
int m[2][N][N];
int dp[2][N][N];
// dp[0][i][j]到i、j时有多少个2；
// dp[1][i][j]到i、j时有多少个5；
int vis[2][N][N];

int work(int mark)
{
    vis[mark][1][1] = 0;
    dp[mark][1][1] = m[mark][1][1];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == 1 && j == 1)
            {
                continue;
            }
            if (i == 1)
            {
                dp[mark][i][j] = dp[mark][i][j - 1] + m[mark][i][j];
                vis[mark][i][j] = 1; // 向右
            }
            else if (j == 1)
            {
                dp[mark][i][j] = dp[mark][i - 1][j] + m[mark][i][j];
                vis[mark][i][j] = 0; // 向下
            }
            else
            {
                int tt1 = dp[mark][i - 1][j];
                int tt2 = dp[mark][i][j - 1];
                if (tt1 < tt2)
                {
                    dp[mark][i][j] = tt1 + m[mark][i][j];
                    vis[mark][i][j] = 0;
                }
                else
                {
                    dp[mark][i][j] = tt2 + m[mark][i][j];
                    vis[mark][i][j] = 1;
                }
            }
        }
    }
    return dp[mark][n][n];
}

void print(int mark, int x, int y)
{
    if (x == 1 && y == 1)
    {
        return;
    }
    if (vis[mark][x][y] == 0)
    {
        print(mark, x - 1, y);
        cout << "D";
    }
    else
    {
        print(mark, x, y - 1);
        cout << "R";
    }
}

void solve()
{
    cin >> n;
    memset(vis, 0, sizeof(vis));
    memset(m, 0, sizeof(m));
    int has0 = false;
    int tt, x, y;
    int t2, t5;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> tt;
            if (tt == 0)
            {
                has0 = true;
                x = i, y = j;
                continue;
            }
            t2 = t5 = tt;
            while (t2 % 2 == 0)
            {
                t2 /= 2;
                m[0][i][j]++;
            }
            while (t5 % 5 == 0)
            {
                t5 /= 5;
                m[1][i][j]++;
            }
        }
    }

    int ans2 = work(0); // 路径存在最少的2的个数
    int ans5 = work(1); // 路径存在最少的5的个数

    int mark = 0;
    int ans = 0;
    if (ans2 < ans5)
    {
        ans = ans2;
        mark = 0;
    }
    else
    {
        ans = ans5;
        mark = 1;
    }
    if (has0 && ans > 1)
    {
        cout << 1 << endl; // 有零存在那么最终结果就只有一个零
        for (int i = 2; i <= x; i++)
        {
            // 向下到有零的那一行
            cout << "D";
        }
        for (int j = 2; j <= n; j++)
        {
            // 走到最右边
            cout << "R";
        }
        for (int i = x + 1; i <= n; i++)
        {
            // 走到最下边
            cout << "D";
        }
        cout << endl;
        return;
    }
    cout << ans << endl;
    print(mark, n, n);
    cout << endl;
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    FILE *in = freopen("in.txt", "r", stdin);
    FILE *out = freopen("out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}