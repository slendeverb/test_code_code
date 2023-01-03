typedef long long ll;
const int N = 5e6 + 10;
const int p = 1e9 + 7;
ll inv[N], n, a[N], s[N], sv[N];

void exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}
int ext_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int d = ext_gcd(b, a % b, x, y);
    int tmp = y;
    y = x - a / b * y;
    x = tmp;
    return d;
}
int inverse1(int a, int b)
{
    int x, y;
    int d = ext_gcd(a, b, x, y);
    x = (x % p + p) % p;
    return x;
}

int qpow(int x, int b, int mod)
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
        inv[i] = (ll)(p - p / i) * inv[p % i] % p;
    }
}

void inverse2()
{
    s[0] = 1;
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] * a[i] % p;
    sv[n] = qpow(s[n], p - 2, p);
    // 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
    for (int i = n; i >= 1; --i)
        sv[i - 1] = sv[i] * a[i] % p;
    for (int i = 1; i <= n; ++i)
        inv[i] = sv[i] * s[i - 1] % p;
}