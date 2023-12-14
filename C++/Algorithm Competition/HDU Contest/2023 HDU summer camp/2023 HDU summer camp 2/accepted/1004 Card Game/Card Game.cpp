#include <iostream>
using namespace std;

const int mod = 998244353;

long long qpow(long long a, long long b)
{
    a = (a % mod + mod) % mod;
    long long res = 1;
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

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        cout << (qpow(2, n - 1) - 1) % mod << "\n";
    }
    return 0;
}