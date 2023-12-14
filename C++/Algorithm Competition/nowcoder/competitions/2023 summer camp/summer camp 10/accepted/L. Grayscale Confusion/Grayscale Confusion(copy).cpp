#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using LL = long long;
using ld = long double;
using ull = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<long long, long long>;
using unl = __int128;
#define INF 1000000000
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
using UID = uniform_int_distribution<int>;

const int N = 1005;
int n, c[N][3];
double f[3];

// 考虑采用线性函数 f(r, g, b) = x*r + y*g + z*b，对 RGB 的系数和为一且均非负。

// 可以发现，只有 RGB 各自增 1 才能满足偏序，因此所有满足偏序的颜色对都能被区分开。

// 对于需要混淆的两个颜色：

// 如果有 RGB 中的一者相等，假设是 R 相等，直接令系数为 (1, 0, 0)。

// 如果满足偏序关系，则寄掉。

// 否则一定存在交错，假设 r1 > r2，g1 < g2，令 r1 - r2 = p, g2 - g1 = q，那么令：

// x = q / (p + q)
// y = p / (p + q)
// z = 0
// 就可以实现混淆这两个颜色。

void print()
{
    for (int i = 1; i <= n; i++)
    {
        double res = 0.0;
        for (int j = 0; j < 3; j++)
        {
            res += f[j] * c[i][j];
        }
        cout << lround(res) << '\n';
    }
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> c[i][j];
        }
    }

    int eq = -1;
    for (int i = 0; i < 3; i++)
    {
        if (c[1][i] == c[2][i])
        {
            eq = i;
            break;
        }
    }

    if (eq != -1)
    {
        f[eq] = 1;
        print();
        return;
    }

    int lt = -1, gt = -1;
    for (int i = 0; i < 3; i++)
    {
        if (c[1][i] < c[2][i])
        {
            lt = i;
        }
        else
        {
            gt = i;
        }
    }

    if (lt == -1 || gt == -1)
    {
        cout << "-1\n";
        return;
    }

    int dl = c[2][lt] - c[1][lt];
    int dg = c[1][gt] = c[2][gt];
    f[gt] = (double)dl / (dl + dg);
    f[lt] = (double)dg / (dl + dg);
    print();
}

signed main()
{
    // IOS;
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}