// 萌新推荐写法,初学者也可以全开long long：
// x的b次方模mod
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

//

const int p = 1e9 + 7;

inline int qpow(long long a, int b)
{
    int ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1)
    {
        if (b & 1)
            ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}