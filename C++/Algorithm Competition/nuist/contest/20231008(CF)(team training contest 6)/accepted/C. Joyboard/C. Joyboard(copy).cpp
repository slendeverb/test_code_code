#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m, k;

void solve()
{
    cin >> n >> m >> k;
    int ans = 0;
    if (k == 1)
    {
        ans = 1;
    }
    else if (k == 2)
    {
        if (m <= n)
        {
            ans = m;
        }
        else
        {
            ans = n + (m - n) / n;
        }
    }
    else if (k == 3)
    {
        if (m <= n)
        {
            ans = 0;
        }
        else
        {
            ans = m - n - (m - n) / n;
        }
    }
    else
    {
        ans = 0;
    }
    cout << ans << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}
