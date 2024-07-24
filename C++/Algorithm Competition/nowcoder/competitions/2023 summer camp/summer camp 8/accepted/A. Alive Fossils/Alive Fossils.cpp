#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, c;
string s;
vector<string> v;
map<string, int> m;

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> c;
        for (int j = 1; j <= c; j++)
        {
            cin >> s;
            m[s]++;
        }
    }
    for (auto i : m)
    {
        if (i.second == n)
        {
            v.push_back(i.first);
        }
    }
    sort(v.begin(), v.end());
    cout << v.size() << "\n";
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}