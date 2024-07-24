#include <iostream>
using namespace std;

typedef long long ll;

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
    ll b, p, m;
    while (scanf("%lld%lld%lld", &b, &p, &m) != EOF)
    {
        int ans = qpow(b, p, m);
        cout << ans << "\n";
    }
    return 0;
}