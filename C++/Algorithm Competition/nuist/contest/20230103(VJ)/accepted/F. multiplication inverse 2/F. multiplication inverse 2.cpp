#include <iostream>
using namespace std;

typedef long long ll;
const int N = 5e6 + 10;
const int p = 1e9 + 7;
const int M = 998244353;
ll n, a[N], s[N], inv[N], sv[N], m[N];

ll qpow(ll x, ll b, ll mod)
{
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return x % mod;
    }
    ll tmp = qpow(x, b / 2, mod);
    tmp = tmp * tmp % mod;
    if (b % 2 == 0)
    {
        return tmp;
    }
    else
    {
        return tmp * x % mod;
    }
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    m[0] = 1;
    for (int i = 1; i < n; i++)
    {
        m[i] = m[i - 1] * M % p;
    }
    s[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        s[i] = s[i - 1] * a[i] % p;
    }
    sv[n] = qpow(s[n], p - 2, p);
    for (int i = n; i >= 1; --i)
    {
        sv[i - 1] = sv[i] * a[i] % p;
    }
    for (int i = 1; i <= n; ++i)
    {
        inv[i] = sv[i] * s[i - 1] % p;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = (ans + m[n - i] * inv[i] % p) % p;
    }
    cout << ans << "\n";
    return 0;
}