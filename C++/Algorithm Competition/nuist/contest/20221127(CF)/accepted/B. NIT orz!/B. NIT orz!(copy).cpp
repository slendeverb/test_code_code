#include <bits/stdc++.h>
using namespace std;

#define int long long

int t, n, m;

const int N = 3e5 + 10;

void solve()
{
    int n, z;
    cin >> n >> z;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        ans = max(ans, x | z);
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}