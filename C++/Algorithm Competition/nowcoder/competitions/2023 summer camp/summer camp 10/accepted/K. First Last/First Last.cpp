#include <bits/stdc++.h>
using namespace std;
#define ll long long
long double binpow1(long double a, ll b)
{
    long double res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    if (n > 1)
        cout << fixed << setprecision(15) << (long double)binpow1(1.0 * 2 / n, m) << endl;
    else
        cout << fixed << setprecision(15) << 1.0 << endl;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }

    return 0;
}