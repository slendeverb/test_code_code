#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 1e5 + 5;
int n;
int now[N];

struct Interval
{
    int l, r;
    void input()
    {
        cin >> l >> r;
    }
} a[N];

void solve()
{
    cin >> n;
    memset(now, 0, sizeof(now));
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        a[i].input();
    }
    for (int i = 29; i >= 0; i--)
    {
        bool flag = true;
        for (int j = 1; j <= n && flag; j++)
        {
            int nl = now[j] | (1 << i);
            int nr = now[j] | ((2 << i) - 1);
            if (nl > a[j].r || nr < a[j].l)
            { // 区间没有交集，答案无法填 1
                flag = false;
                break;
            }
        }
        if (flag)
        { // 答案可以填 1 的情况
            for (int j = 1; j <= n; j++)
            {
                now[j] |= (1 << i);
            }
            ans |= (1 << i);
        }
        else
        { // 答案只能填 0 的情况，看每个数的第 i 位填什么
            for (int j = 1; j <= n; j++)
            {
                int nl = now[j] | (1 << i);
                int nr = now[j] | ((2 << i) - 1);
                if (nl <= a[j].r && nr >= a[j].l && nl - 1 < a[j].l)
                {
                    now[j] |= (1 << i);
                }
            }
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