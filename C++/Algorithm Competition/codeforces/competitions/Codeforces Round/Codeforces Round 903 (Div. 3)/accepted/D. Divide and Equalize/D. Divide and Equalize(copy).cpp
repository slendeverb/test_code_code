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

void addDivs(int x, map<int, int> &divs)
{
    int i = 2;
    while (i * i <= x)
    {
        while (x % i == 0)
        {
            divs[i]++;
            x /= i;
        }
        i++;
    }
    if (x > 1)
    {
        divs[x]++;
    }
}

void solve()
{
    int n = 0;
    cin >> n;
    vector<int> a(n);
    map<int, int> divs;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        addDivs(a[i], divs);
    }
    for (auto &elem : divs)
    {
        if (elem.second % n != 0)
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}