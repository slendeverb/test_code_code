#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 5e5 + 5;
int n, m;
struct node
{
    int a, b;
    void input()
    {
        cin >> a >> b;
    }
    bool operator<(const node &x) const
    {
        return a - b > x.a - x.b;
    }
} p[N];

void solve()
{
    cin >> n >> m;
    int ans = 0;
    int tmp = 0;
    for (int i = 1; i <= n; i++)
    {
        p[i].input();
        tmp += p[i].b;
    }
    sort(p + 1, p + 1 + n);
    if (m >= 2 * n - 1)
    {
        ans = tmp;
    }
    tmp += (p[1].a - p[1].b);
    for (int i = 2; i <= n; i++)
    {
        tmp += p[i].a - p[i].b;
        if (2 * n - i <= m)
        {
            ans = max(ans, tmp);
        }
    }
    cout << ans << endl;
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    FILE *in = freopen("./test/in.txt", "r", stdin), *out = freopen("./test/out.txt", "w", stdout);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}