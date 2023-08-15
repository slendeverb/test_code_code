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

void print(unl x)
{
    if (x < 0)
    {
        x = -x;
        putchar('-');
    }
    if (x > 9)
    {
        print(x / 10);
    }
    putchar(x % 10 + '0');
}

const int N = 1e5 + 5;
int n, a[N];

void solve()
{
    cin >> n;
    LL sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    unl ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += ((unl)sum - a[i]) * a[i];
    }
    print(ans / 2);
    cout << endl;
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