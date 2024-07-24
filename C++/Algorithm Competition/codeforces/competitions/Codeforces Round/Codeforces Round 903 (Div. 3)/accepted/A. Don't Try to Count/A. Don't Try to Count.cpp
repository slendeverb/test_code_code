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

int n, m;
string x, s;

class KMP
{
    string b;

public:
    vector<int> nx;
    KMP(string b)
    {
        this->b = b;
        int n = b.size(), j = 0;
        nx.resize(n);
        for (int i = 1; i < n; i++)
        {
            while (j > 0 && b[i] != b[j])
            {
                j = nx[j - 1];
            }
            if (b[i] == b[j])
            {
                j++;
            }
            nx[i] = j;
        }
    }
    int matchTimes(string a)
    {
        int n = b.size(), m = a.size(), j = 0, ans = 0;
        for (int i = 0; i < m; i++)
        {
            while (j > 0 && a[i] != b[j])
            {
                j = nx[j - 1];
            }
            if (a[i] == b[j])
            {
                j++;
            }
            if (j == n)
            {
                ans++;
                j = nx[j - 1];
            }
        }
        return ans;
    }
};

void solve()
{
    cin >> n >> m;
    cin >> x >> s;
    int ans = 0;
    KMP kmp(s);
    while (true)
    {
        int cnt = kmp.matchTimes(x);
        if (cnt == 0)
        {
            if (x.size() >= (s.size() << 1) && ans >= 2)
            {
                ans = -1;
                break;
            }
            else
            {
                x = x + x;
                ans++;
                continue;
            }
        }
        else
        {
            break;
        }
    }
    cout << ans << "\n";
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