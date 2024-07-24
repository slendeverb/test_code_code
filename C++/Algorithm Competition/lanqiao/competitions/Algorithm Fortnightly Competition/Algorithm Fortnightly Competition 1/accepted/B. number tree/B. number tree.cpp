// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

#define int long long

int n, q;
string s;

void solve()
{
    cin >> n >> q;
    while (q--)
    {
        cin >> s;
        int ans = 0;
        int len = s.size();
        int l = 1, r = (1 << len);
        for (int i = 0; i < len; i++)
        {
            int mid = ((r - l) >> 1) + l;
            if (s[i] == 'L')
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