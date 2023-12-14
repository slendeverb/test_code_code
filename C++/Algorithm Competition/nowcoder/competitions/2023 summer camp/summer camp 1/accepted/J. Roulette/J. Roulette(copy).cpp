#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
const ll mod = 998244353;

ll qpow(ll a, ll b)
{
    ll res = 1;
    a = (a % mod + mod) % mod;
    while (b)
    {
        if (b & 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

int main()
{
    ll n, m;
    cin >> n >> m;
    ll goal = n + m;
    ll ans = 1;
    while (n < goal)
    {
        ll i = log2(n + 1);
        ll r = min(goal, (1ll << (i + 1)) - 1);
        ans = (ans * qpow(mod + 1 - qpow(2, mod - 1 - i), r - n)) % mod;
        n = r;
    }
    cout << ans << "\n";
    return 0;
}