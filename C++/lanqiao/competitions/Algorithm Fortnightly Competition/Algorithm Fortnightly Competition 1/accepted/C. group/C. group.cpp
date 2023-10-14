// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#define int long long

const int N = 1e5 + 5;
int n, k;
int h[N];

bool check(int mid)
{
    int cnt = 0;
    int l = 1, r = 1;
    while (r <= n)
    {
        if (h[r] - h[l] <= mid)
        {
            r++;
        }
        else
        {
            cnt++;
            l = r;
        }
    }
    cnt++;
    return cnt <= k;
}

void solve()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> h[i];
    }
    sort(h + 1, h + 1 + n);
    int l = 0, r = h[n] - h[1];
    while (l < r)
    {
        int mid = (r - l) / 2 + l;
        if (check(mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << l << "\n";
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