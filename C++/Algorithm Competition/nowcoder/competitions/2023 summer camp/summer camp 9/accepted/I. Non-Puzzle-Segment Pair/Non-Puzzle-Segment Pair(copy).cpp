#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
const int MOD = 1e9 + 7;

int n, k, ans;
long long _2pow[N], num[N];

vector<int> in[N], out[N];

void solve()
{
    cin >> n;
    _2pow[0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        _2pow[i] = (_2pow[i - 1] << 1) % MOD;
    }

    for (int i = 1, l, r; i <= n; ++i)
    {
        cin >> l >> r;
        in[l].push_back(i), out[r + 1].push_back(i);

        cin >> l >> r;
        in[l].push_back(i), out[r + 1].push_back(i);
    }

    int tot = 0, mx = (int)5e5, lst = mx + 1;
    for (int i = 1; i <= mx; i++)
    {
        for (int it : out[i])
        {
            if (num[it] == 2)
            {
                --k;
            }

            --num[it];

            if (!num[it])
            {
                --tot;
            }
        }

        if (tot < n)
        {
            lst = mx + 1;
        }
        else
        {
            lst = k;
        }

        for (int it : in[i])
        {
            if (!num[it])
            {
                ++tot;
            }

            ++num[it];

            if (num[it] == 2)
            {
                ++k;
            }

            if (tot == n)
            {
                if (lst == mx + 1 || k > lst)
                {
                    ans = ((ans + MOD - _2pow[lst]) % MOD + _2pow[k]) % MOD;
                }
                lst = k;
            }
        }
    }
    cout << ans << "\n";
}

signed main()
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