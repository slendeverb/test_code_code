#include <iostream>
using namespace std;

const int mod = 1e9 + 7;

int A(int n, int m)
{
    int res = 1;
    for (int i = m; i >= 1; i--)
    {
        res *= n; // n × n-1 × n-2 × ... n-m，m就是需要减1的次数
        n--;
    }
}

//

#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;
const int MAXN = 2e5 + 5;

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
