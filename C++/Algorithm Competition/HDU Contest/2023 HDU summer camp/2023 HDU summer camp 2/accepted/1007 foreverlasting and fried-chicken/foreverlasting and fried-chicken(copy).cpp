#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

const int MAXN = 1010;
const int MOD = 1e9 + 10;
bitset<MAXN> b[MAXN]; // 用bitset优化

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

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    init();
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        long long ans = 0;
        for (int i = 1; i <= m; i++)
        {
            b[i].reset();
        }
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            cin >> u >> v;
            b[u][v] = b[v][u] = 1;
        }

        for (int i = 1; i <= n - 1; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                int cnt_i = b[i].count();
                int cnt_j = b[j].count();
                int cnt = (b[i] & b[j]).count();

                if (b[i][j]) // 去掉i和j相邻的情况
                {
                    cnt_i--, cnt_j--;
                }
                ans = (ans + C(cnt, 4) * C(cnt_i - 4, 2) + C(cnt, 4) * C(cnt_j - 4, 2)) % MOD;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}