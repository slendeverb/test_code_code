#include <iostream>
using namespace std;

const int maxn = 2e5 + 10;
int a[maxn];
const int mod = 998244353;

long long C(long long n, long long m)
{
    long long ans = 1;
    m = min(m, n - m);
    for (long long i = 1; i <= m; i++)
    {
        ans = ans * (n - m + i) / i % mod;
    }
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        long long sum = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            sum = (sum + a[i]) % mod;
        }
        for (int i = 1; i <= m; i++)
        {
            cout << (C(n - 1, i - 1) % mod * sum % mod) % mod << " ";
        }
        cout << "\n";
    }
    return 0;
}