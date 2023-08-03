#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
const int MOD = 1e9 + 7;

struct node
{
    long long k, b, p;
} a[MAXN];

long long sum[MAXN];
long long mul[MAXN];

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
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int n, q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].k;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].b;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].p;
        }
        long long x, l, y;
        while (q--)
        {
            cin >> x >> l >> y;
            int pos = a[x].p;
            int m = 1;
            sum[m] = a[pos].b;
            for (int i = a[pos].p; m <= n - 1; i = a[i].p)
            {
                m++;
                sum[m] = (sum[m - 1] * a[i].k % MOD + a[i].b) % MOD;
            }
            int m2 = 0;
            mul[m2] = 1;
            for (int i = pos; m2 <= n - 1; i = a[i].p)
            {
                m2++;
                mul[m2] = (mul[m2 - 1] * a[i].k) % MOD;
            }
            long long tmp1 = l / n;
            long long tmp2 = l % n;
            long long ans = ((y * quick_pow(mul[m2], tmp1) % MOD * mul[tmp2]) % MOD);
            long long tmps = 0;
            for (int i = 1; i <= tmp1; i++)
            {
                tmps = (tmps * mul[m2] % MOD + sum[m]) % MOD;
            }
            tmps = (tmps * mul[tmp2] + sum[tmp2]) % MOD;
            ans = (ans + tmps) % MOD;
            cout << ans << "\n";
        }
    }
    cout.flush();
    return 0;
}