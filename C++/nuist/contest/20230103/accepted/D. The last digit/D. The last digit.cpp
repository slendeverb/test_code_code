#include <iostream>
using namespace std;

typedef long long ll;
const int mod = 10;

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

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll a, b;
        cin >> a >> b;
        int ans = qpow(a, b, 10);
        cout << ans << "\n";
    }
    return 0;
}