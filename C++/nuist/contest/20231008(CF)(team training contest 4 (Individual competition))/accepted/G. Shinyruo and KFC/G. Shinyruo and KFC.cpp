#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int N = 5e4 + 5;
int n, m;
vector<long long> fact(N), invFact(N);
map<int, int> mp;

long long quickPow(long long a, long long b)
{
    a %= MOD;
    long long res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

long long inv(long long a)
{
    return quickPow(a, MOD - 2);
}

void init()
{
    fact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = fact[i - 1] * i % MOD;
    }
    invFact[N - 1] = inv(fact[N - 1]);
    for (int i = N - 2; i >= 0; i--)
    {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }
}

long long C(int n, int k)
{
    if (k < 0 || k > n)
    {
        return 0;
    }
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

void solve()
{
    cin >> n >> m;
    int maxx = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        maxx = max(maxx, x);
        mp[x]++;
    }
    for (int k = 1; k <= m; k++)
    {
        if (k < maxx)
        {
            cout << "0\n";
            continue;
        }
        else
        {
            long long ans = 1;
            for (auto it : mp)
            {
                ans = (ans * quickPow(C(k, it.first), it.second)) % MOD;
            }
            cout << ans << "\n";
        }
    }
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    init();
    while (T--)
    {
        solve();
    }
    return 0;
}