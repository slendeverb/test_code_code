#include <iostream>
using namespace std;

#define int long long

const int maxn = 2e6 + 10;
const int mod = 998244353;
char a[maxn];
int s[maxn], sv[maxn], inv[maxn], p[maxn], n;
long long ans;

long long qpow(long long a, int b, int mod)
{
    long long res = 1;
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

signed main()
{
    cin >> n;
    scanf("%s", a + 1);
    long long inv100 = qpow(100LL, mod - 2, mod);
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> p[i];
    }
    ans = a[n] - '0';
    long long tmp = 1;
    for (int i = n - 1; i >= 1; i--)
    {
        tmp = (tmp * 10 % mod * (100 - p[i]) % mod * inv100 % mod + p[i] * inv100 % mod) % mod;
        ans = (ans + (a[i] - '0') * tmp % mod) % mod;
    }
    cout << ans << "\n";
    return 0;
}