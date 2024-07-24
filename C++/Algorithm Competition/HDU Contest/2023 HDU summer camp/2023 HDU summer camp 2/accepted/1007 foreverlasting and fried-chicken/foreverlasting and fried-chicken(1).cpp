#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int maxn = 1010;
const int mod = 1e9 + 7;
const int MAXN = maxn * (maxn - 1) / 2 + 10;
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

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    init();
    while (t--)
    {
        set<int> s[maxn];
        long long ans = 0;
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            cin >> u >> v;
            s[u].insert(v);
            s[v].insert(u);
        }
        for (int i = 1; i <= n - 1; i++)
        {
            int size_i = s[i].size();
            if (s[i].size() < 4)
            {
                continue;
            }
            for (int j = i + 1; j <= n; j++)
            {
                if (s[i].count(j))
                {
                    continue;
                }
                long long cnt = 0;
                int size_j = s[j].size();
                if (size_i >= 6 || size_j >= 6)
                {
                    for (auto to : s[i])
                    {
                        if (s[j].count(to))
                        {
                            cnt++;
                        }
                    }
                    if (cnt >= 4)
                    {
                        if (size_i - 4 >= 2)
                        {
                            ans = (ans + C(cnt, 4) * C(size_i - 4, 2)) % mod;
                        }
                        if (size_j - 4 >= 2)
                        {
                            ans = (ans + C(cnt, 4) * C(size_j - 4, 2)) % mod;
                        }
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    cout.flush();
    return 0;
}