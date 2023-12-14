#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 1e5 + 5;
int n;

struct node
{
    int a, b;
    void input()
    {
        cin >> a >> b;
    }
    bool operator<(const node &x) const
    {
        return a > x.a;
    }
} t[N];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        t[i].input();
    }
    int x = t[1].a;
    int flag = 1;
    for (int i = 2; i <= n; i++)
    {
        if (t[i].a != x)
        {
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        cout << 0 << endl;
        return;
    }
    sort(t + 1, t + 1 + n);
    int l = 1, r = n;
    int ans = 0;
    while (l < r)
    {
        if (t[l].a == t[r].a)
        {
            break;
        }
        int tradeTimes = min(t[l].b, t[r].b);
        while (t[l].b && t[r].b)
        {
            ans += (t[l].a - t[r].a) * tradeTimes;
            t[l].b -= tradeTimes;
            t[r].b -= tradeTimes;
        }
        if (t[l].b || t[r].b)
        {
            if (t[l].b)
            {
                r--;
            }
            else
            {
                l++;
            }
        }
        else
        {
            l++, r--;
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