#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;

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

vector<int> cnt;
vector<int> edge;
vector<int> num;

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T, n, m, u, v;
    cin >> T;
    init();
    while (T--)
    {
        cin >> n >> m;
        edge.assign(n + 1, 0);
        int ans = 0;
        int maxx = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> u >> v;
            edge[u]++;
            edge[v]++;
            maxx = max(max(maxx, edge[u]), edge[v]);
        }
        num.assign(n, 0);
        cnt.assign(n, 0);
        for (int i = 1; i <= n; i++)
        {
            num[edge[i]]++;
        }
        for (int i = 2; i <= maxx; i++)
        {
            if (num[i] > 0)
            {
                for (int j = 2; j <= i; j++)
                {
                    cnt[j] = (1ll * cnt[j] % MOD + num[i] * C(i, j) % MOD) % MOD;
                }
            }
        }
        for (int i = 2; i <= n - 1; i++)
        {
            ans ^= cnt[i];
        }
        cout << ans << "\n";
    }
    cout.flush();
    return 0;
}