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

int a, b, c;

void solve()
{
    cin >> a >> b >> c;
    priority_queue<int, vector<int>, less<int>> pq;
    if (a == b && b == c)
    {
        cout << "YES\n";
    }
    else
    {
        pq.emplace(a), pq.emplace(b), pq.emplace(c);
        int minn = min(a, min(b, c));
        for (int i = 0; i < 3; i++)
        {
            int x = pq.top();
            pq.pop();
            int x1 = minn, x2 = x - x1;
            minn = min(minn, x2);
            pq.emplace(x1), pq.emplace(x2);
            if (minn == pq.top())
            {
                break;
            }
        }
        if (minn == pq.top())
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
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