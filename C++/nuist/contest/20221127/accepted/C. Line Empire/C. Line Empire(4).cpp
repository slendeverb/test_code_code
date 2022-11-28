#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
#define ll LL

int t, n, m;

const int N = 3e5 + 10;
ll x[N];
ll sum[N];

void solve()
{
    ll a, b;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    for (int i = n; i >= 1; i--)
    {
        sum[i] = sum[i + 1] + x[i];
    }
    ll ans = 0;
    ll pos = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += b * (x[i] - pos);
        if ((sum[i + 1] - (n - i) * pos) * b >= (sum[i + 1] - (n - i) * x[i]) * b + a * (x[i] - pos))
        {
            ans += a * (x[i] - pos);
            pos = x[i];
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> t;
    while (t--)
        solve();
    return 0;
}