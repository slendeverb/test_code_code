#include <iostream>
using namespace std;

const int MOD = 998244353;

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

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        long long n, m, k;
        cin >> n >> m >> k;
        long long ans = 0;
        if (k < n)
        {
            ans = quick_pow(m, n - k);
        }
        else
        {
            ans = quick_pow(m, n);
        }
        cout << ans << "\n";
    }
    return 0;
}