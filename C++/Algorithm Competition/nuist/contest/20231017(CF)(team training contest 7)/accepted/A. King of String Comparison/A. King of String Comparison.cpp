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
#include <algorithm>
using namespace std;

#define int long long

const int N = 2e5 + 5;
int n;
string s, t;

void solve()
{
    cin >> n;
    cin >> s >> t;
    long long ans = 0;
    for (int l = 0, r = 0; l <= r && r < n; r++)
    {
        if (s[r] < t[r])
        {
            ans += (r - l + 1) * (n - 1 - r + 1);
            l = r + 1;
        }
        if (s[r] > t[r])
        {
            l = r + 1;
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