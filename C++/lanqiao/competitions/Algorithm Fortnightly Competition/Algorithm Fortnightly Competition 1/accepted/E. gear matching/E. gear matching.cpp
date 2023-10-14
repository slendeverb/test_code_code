// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define int long long

int n;
string s, t;

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
    int firstMatchLocation(string a)
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
                return i - n + 1;
            }
        }
        return -1;
    }
};

void solve()
{
    cin >> n;
    cin >> s >> t;
    for (int i = 0; i < n; i++)
    {
        if (isupper(s[i]))
        {
            s[i] += ('a' - 'A');
        }
        else
        {
            s[i] -= ('a' - 'A');
        }
    }
    s = s + s;
    KMP kmp(t);
    int ans = kmp.firstMatchLocation(s);
    if (ans != -1)
    {
        cout << "Yes\n";
        ans = min(ans, n - ans);
        cout << ans << "\n";
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
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}