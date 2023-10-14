// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#define int long long

const int N = 2e5 + 5;
const int M = 55;
int n, m, q;
int t[N], _2powk[M];

struct node
{
    int k, s;
} fitnessPlan[M];

bool cmp(const node &x, const node &y)
{
    if (x.s == y.s)
    {
        return x.k < y.k;
    }
    return x.s > y.s;
}

long long qpow(long long a, long long b)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve()
{
    cin >> n >> m >> q;
    for (int i = 1; i <= q; i++)
    {
        cin >> t[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> fitnessPlan[i].k >> fitnessPlan[i].s;
    }
    int sum = 0;
    int pos = 1;
    sort(t + 1, t + 1 + q);
    sort(fitnessPlan + 1, fitnessPlan + 1 + m, cmp);
    for (int i = 1; i <= m; i++)
    {
        _2powk[i] = qpow(2, fitnessPlan[i].k);
    }
    for (int i = 1; i <= q; i++)
    {
        int time = t[i] - pos;
        while (time > 0ll)
        {
            for (int j = 1; j <= m;)
            {
                if (_2powk[j] <= time)
                {
                    sum += fitnessPlan[j].s;
                    time = max(0ll, time - _2powk[j]);
                }
                else
                {
                    if (time == 0ll)
                    {
                        break;
                    }
                    j++;
                }
            }
        }
        pos = t[i] + 1;
    }
    if (pos != n + 1)
    {
        int time = n - pos + 1;
        while (time > 0ll)
        {
            for (int j = 1; j <= m;)
            {
                if (_2powk[j] <= time)
                {
                    sum += fitnessPlan[j].s;
                    time = max(0ll, time - _2powk[j]);
                }
                else
                {
                    if (time == 0ll)
                    {
                        break;
                    }
                    j++;
                }
            }
        }
    }
    cout << sum << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}