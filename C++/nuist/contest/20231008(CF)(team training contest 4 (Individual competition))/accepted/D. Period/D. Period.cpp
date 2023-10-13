#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int p = 131;
long long hs[N], b_pow[N];
string s;
int n, q, x, ans[N];

void initHash()
{
    b_pow[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        hs[i] = hs[i - 1] * p + s[i] - 'a' + 1;
        b_pow[i] = b_pow[i - 1] * p;
    }
}

long long getSub(int l, int r)
{
    return hs[r] - hs[l - 1] * b_pow[r - l + 1];
}

void solve()
{
    cin >> s;
    s = ' ' + s;
    n = s.size() - 1;
    initHash();
    for (int i = 1; i <= n / 2; i++)
    {
        if (getSub(1, i) == getSub(n - i + 1, n))
        {
            ans[i] = ans[i - 1] + 1;
        }
        else
        {
            ans[i] = ans[i - 1];
        }
    }
    cin >> q;
    while (q--)
    {
        cin >> x;
        cout << ans[min(x - 1, n - x)] << "\n";
    }
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}