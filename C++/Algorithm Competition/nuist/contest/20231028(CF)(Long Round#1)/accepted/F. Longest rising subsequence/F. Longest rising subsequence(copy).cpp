#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 1e6 + 5;
int n;

void solve()
{
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<int>> pos(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] > i)
        {
            cout << "-1\n";
            return;
        }
        pos[a[i]].emplace_back(i);
    }
    int cur = 1;
    vector<int> p(n);
    for (int i = 1; i <= n; i++)
    {
        reverse(pos[i].begin(), pos[i].end());
        if (!pos[i].size())
        {
            break;
        }
        for (int x : pos[i])
        {
            p[x - 1] = cur++;
        }
    }
    if (cur > n)
    {
        for (int x : p)
        {
            cout << x << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "-1\n";
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("C:/Users/slendeverb/Documents/code_code/test/in.txt", "r", stdin);
    freopen("C:/Users/slendeverb/Documents/code_code/test/out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}