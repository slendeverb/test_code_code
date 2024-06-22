#include <iostream>
using namespace std;

const int mod = 1e9 + 7;

long long A(long long n, long long m)
{
    int res = 1;
    for (int i = m; i >= 1; i--)
    {
        res *= n; // n × n-1 × n-2 × ... n-m，m就是需要减1的次数
        n--;
    }
}

long long C(long long n, long long m)
{
    long long ans = 1;
    m = min(m, n - m);
    for (long long i = 1; i <= m; i++)
    {
        ans = ans * (n - m + i) / i; // 注意一定要先乘再除
    }
    return ans;
}

//

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;
const int N = 2e5 + 5;

long long quick_pow(long long a, long long b)
{
    a = (a % MOD + MOD) % MOD;
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

vector<long long> fact(N), invFact(N);

void init()
{
    fact[0] = 1;
    for (int i = 1; i < N; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    invFact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; --i)
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

long long C(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

long long A(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    return fact[n] * invFact[n - k] % MOD;
}
