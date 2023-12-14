#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
#define endl '\n'
using LL = long long;
using ld = long double;
using ull = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<long long, long long>;
using unl = __int128;
#define INF 1000000000
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
using UID = uniform_int_distribution<int>;

const int N = 5e5 + 5;
int n, a[N];
map<int, int> cnt;

void solve()
{
    cnt.clear();
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        cnt[a[i]]++;
    }
    bool flag = 0;
    int minn;
    if (cnt.size() > 1)
    {
        for (auto it : cnt)
        {
            if (!flag)
            {
                minn = it.second;
                flag = 1;
            }
            else
            {
                if (minn < it.second)
                {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
    return;
}

signed main()
{
    // IOS;
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    return 0;
}