#include <bits/stdc++.h>
using namespace std;

long long x, a, b, ans;

void solve()
{
    ans = 0;
    cin >> x >> a >> b;
    while (x && ans <= 100)
    {
        x = min(x - 1, min((x + a) >> 1, (long long)floor(sqrt(x + b))));
        ans++;
    }
    cout << ans + x << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}