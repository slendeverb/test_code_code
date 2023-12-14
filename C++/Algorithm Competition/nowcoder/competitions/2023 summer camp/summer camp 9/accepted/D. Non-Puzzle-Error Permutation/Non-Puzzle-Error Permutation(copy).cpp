#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
int n, p[N], s[N][N];

void add(int l, int ql, int qr)
{
    s[l][ql]++;
    s[l][qr + 1]--;
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            s[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int nr = i, r = i, sum = 0; // sum 表示区间内有几个<=p[i]的数
        // 初始1个数不合法，从单个数开始拓展
        for (int l = i; l >= 1; l--) // 维护p[i]作为第i-l+1个最小的数的l,r 区间
        {
            if (p[l] <= p[i])
            {
                sum++; // 左边的数小于右边的数，表示p[i]为第i-l+1个最小的数，显然不合法
            }
            while (r < n && sum < i - l + 1)
            {
                r++, nr = r;
                if (p[r] <= p[i])
                {
                    sum++;
                }
            } // 将sum拓展到i-l+1为止
            if (sum == i - l + 1)
            {
                while (r < n && p[r + 1] > p[i]) // 在维护sum不变的情况下拓展r
                {
                    r++;
                }
                add(l, nr, r);
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            s[i][j] += s[i][j - 1];
            if (!s[i][j] && i <= j)
            {
                ans++;
            }
        }
    }

    cout << ans << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    return 0;
}