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
int n;
int a[N], b[N];

void solve()
{
    cin >> n;
    for (int i = 0; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++)
    {
        cin >> b[i];
    }
    long long ans = 0;
    int need = 0;
    for (int i = n; i >= 1; i--)
    {
        need = b[i] - a[i];
        if (need < 0)
        {
            continue;
        }
        else
        {
            need++;
            need >>= 1;
            b[i] -= (need << 1);
            b[i - 1] += need;
            ans += need;
        }
    }
    for (int i = 0; i <= n; i++)
    {
        if (a[i] < b[i])
        {
            cout << "-1\n";
            return;
        }
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}