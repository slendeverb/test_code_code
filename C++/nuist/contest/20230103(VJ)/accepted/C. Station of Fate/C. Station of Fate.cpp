#include <iostream>
using namespace std;

typedef long long ll;
const ll MOD = 998244353;

ll A(ll m, ll n)
{
    ll ret = 1;
    for (int i = 1; i <= m; i++)
    {
        ret = ret * (n - i + 1) % MOD;
    }
    return ret;
}

int main()
{
    // ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        ll tmp1 = 1;
        ll tmp2 = m;
        for (int i = 1; i <= n - m; i++) // 每次插入一个人就多一个空
        {
            tmp1 = tmp1 * tmp2 % MOD;
            tmp2++;
        }
        ll ans = A(m, n) * tmp1 % MOD;
        cout << ans << "\n";
    }
    return 0;
}