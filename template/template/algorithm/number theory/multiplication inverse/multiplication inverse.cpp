#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
const int mod = 1e9 + 7;
ll inv[N], n, a[N], s[N], sv[N];

int exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, x, y);
    int z = x;
    x = y;
    y = z - y * (a / b);
    if (d < 0)
    {
        d = -d, x = -x, y = -y;
    }
    return d; // d = gcd(a, b), d > 0;
}
int inverse1(int a, int b) // a为要求乘法逆元的数, b为mod, x是a的乘法逆元
{
    int x, y;
    int d = exgcd(a, b, x, y);
    x = (x % mod + mod) % mod;
    return x;
}

long long qpow(int x, int b, int mod)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return x % mod;
    long long tmp = qpow(x, b / 2, mod);
    tmp = tmp * tmp % mod;
    if (b % 2 == 0)
        return tmp;
    else
        return tmp * x % mod;
}

void inverse()
{
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    }
}

void inverse2()
{
    s[0] = 1;
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] * a[i] % mod;
    sv[n] = qpow(s[n], mod - 2, mod);
    // 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
    for (int i = n; i >= 1; --i)
        sv[i - 1] = sv[i] * a[i] % mod;
    for (int i = 1; i <= n; ++i)
        inv[i] = sv[i] * s[i - 1] % mod;
}