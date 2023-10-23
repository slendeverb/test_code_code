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
using namespace std;

#define int long long

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
int n, p;
int a[N];
int fibonacci[N];
int sum[N]; // sum[n]=sigma(0,n)fibonacci[i]

map<int, bool> mp;

void init()
{
    fibonacci[0] = fibonacci[1] = 1;
    sum[0] = 1;
    sum[1] = 2;
    for (int i = 2; i <= N; i++)
    {
        fibonacci[i] = (fibonacci[i - 2] + fibonacci[i - 1]) % MOD;
        sum[i] = (sum[i - 1] + fibonacci[i]) % MOD;
    }
}

int cal(int x)
{
    int len = 0;
    while (x)
    {
        x /= 2;
        len++;
    }
    return len;
}

void solve()
{
    cin >> n >> p;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        mp[a[i]] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        int tmp = a[i];
        bool flag = false;
        while (tmp)
        {
            if (tmp % 2)
            {
                tmp /= 2;
            }
            else if (tmp % 4 == 0)
            {
                tmp /= 4;
            }
            else
            {
                break;
            }
            if (mp.count(tmp))
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            continue;
        }
        int len = cal(a[i]);
        if (p - len >= 0)
        {
            ans = (ans + sum[p - len]) % MOD;
        }
    }
    cout << ans << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    init();
    while (T--)
    {
        solve();
    }
    // cout.flush();
    return 0;
}