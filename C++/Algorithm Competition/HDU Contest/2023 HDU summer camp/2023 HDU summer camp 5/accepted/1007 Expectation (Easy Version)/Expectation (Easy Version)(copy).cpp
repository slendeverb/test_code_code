#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 5;
const int MOD = 998244353;

long long quick_pow(long long a, long long b)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long inv(long long a)
{
    return quick_pow(a, MOD - 2);
}

vector<long long> fact(MAXN), invFact(MAXN);

void init()
{
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    invFact[MAXN - 1] = inv(fact[MAXN - 1]);
    for (int i = MAXN - 2; i >= 0; --i)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

long long C(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

long long power_m[MAXN];
long long numerator[MAXN];

void init_power_m(int n, int m)
{
    power_m[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        power_m[i] = (power_m[i - 1] + quick_pow(i, m)) % MOD;
    }
}

int main()
{
    int T;
    cin >> T;
    init();
    while (T--)
    {
        int n, m, a, b;
        cin >> n >> m >> a >> b;
        init_power_m(n, m);
        long long ans = 0;
        long long inv_a = inv(a);
        long long inv_b_minus_a = inv(b - a);
        long long inv_denominator = quick_pow(inv(b), n);
        numerator[n] = quick_pow(a, n);
        for (int i = n - 1; i >= 1; i--)
        {
            numerator[i] = (((numerator[i + 1] * inv_a) % MOD) * (b - a) % MOD) % MOD;
        }
        for (int i = 1; i <= n; i++)
        {
            ans = (ans + (((numerator[i] * inv_denominator) % MOD) * C(n, i) % MOD) * power_m[i] % MOD) % MOD;
        }
        cout << ans << "\n";
    }
    return 0;
}