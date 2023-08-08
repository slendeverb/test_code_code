#include <bits/stdc++.h>
using namespace std;

int n;

bool check(long long mid)
{
    long long t = n / (2 * mid + 2);
    long long s = t * 2 + max(0LL, (n % (2 * mid + 2)) - 2 * mid);
    return s <= mid;
}

void solve()
{
    cin >> n;
    long long l = 1, r = n, mid, ans;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << ans << "\n";
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