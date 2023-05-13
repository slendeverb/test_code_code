// 思路：用前缀最大值来表示i前面的最大值与i+1的后缀最小值相比较判断

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int r = 1e6 + 10;
int a[r], b[r], c[r];
signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        b[i] = max(b[i - 1], a[i]);
    }
    c[n] = a[n];
    for (int i = n - 1; i >= 1; i--)
    {
        c[i] = min(c[i + 1], a[i]);
    }
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        int w = 0;
        for (int j = i + 1; j <= n; j += i)
        {

            if (c[j] < b[j - 1])
                w = 1;
        }
        if (w == 0)
            res++;
    }
    cout << res;
}