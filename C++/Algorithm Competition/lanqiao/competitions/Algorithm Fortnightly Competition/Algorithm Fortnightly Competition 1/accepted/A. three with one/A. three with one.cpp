// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#define int long long

string s;

void solve()
{
    cin >> s;
    sort(s.begin(), s.end());
    if ((s[0] == s[1] && s[1] == s[2] && s[0] != s[3]) || (s[1] == s[2] && s[2] == s[3] && s[0] != s[1]))
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}