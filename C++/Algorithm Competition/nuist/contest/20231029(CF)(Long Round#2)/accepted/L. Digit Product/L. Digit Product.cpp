#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int MOD = 1e9 + 7;

int l, r;

void solve()
{
    cin >> l >> r;
    int ans = 1;
    if (r - l <= 8)
    {
        for (int i = l; i <= r; i++)
        {
            int tmp = i;
            while (tmp)
            {
                ans = (ans * (tmp % 10)) % MOD;
                tmp /= 10;
            }
        }
    }
    else
    {
        ans = 0;
    }
    cout << ans << endl;
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("./test/in.txt", "r", stdin), freopen("./test/out.txt", "w", stdout);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}