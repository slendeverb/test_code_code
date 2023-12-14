#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using LL = long long;
using ld = long double;
using ull = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<long long, long long>;
using unl = __int128;
#define INF 1000000000
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
using UID = uniform_int_distribution<int>;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

long long quick_pow(long long a, long long b)
{
    a = (a % MOD + MOD) % MOD;
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

int n, k;

void solve()
{
    cin >> n >> k;
    LL ans = fact[n];
    // for (int i = n; i >= 2; --i)
    // {
    //     ans = (ans * min(i - 1, k)) % MOD;
    // }
    if (k == n)
    {
        ans = ans * fact[n - 1] % MOD;
    }
    else
    {
        ans = ans * fact[k] % MOD * quick_pow(k, n - 1 - k) % MOD; // 在i-1==k之前选k,后面都是选i-1
    }
    cout << ans << '\n';
}

signed main()
{
    // IOS;
    int T = 1;
    cin >> T;
    init();
    while (T--)
    {
        solve();
    }
    return 0;
}