const int MOD = 1e9 + 7;

long long quick_pow(long long a, long long b)
{
    a = a % MOD;
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