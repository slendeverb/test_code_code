#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;
int n, p;
struct node
{
    int a, b;
} resident[N];

bool cmp(const node &x, const node &y)
{
    if (x.b == y.b)
    {
        return x.a > y.a;
    }
    else
    {
        return x.b < y.b;
    }
}

void solve()
{
    cin >> n >> p;
    for (int i = 1; i <= n; i++)
    {
        cin >> resident[i].a;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> resident[i].b;
    }
    sort(resident + 1, resident + 1 + n, cmp);
    long long ans = p;
    int num = n - 1;
    if (num == 0)
    {
        cout << ans << "\n";
        return;
    }
    else
    {
        queue<node> q;
        q.emplace(resident[1]);
        int pos = 1;
        while (!q.empty())
        {
            node u = q.front();
            q.pop();
            if (u.b < p)
            {
                int tmp = min(num, u.a);
                ans += tmp * u.b;
                num -= tmp;
                if (num == 0)
                {
                    cout << ans << "\n";
                    return;
                }
                int cnt = 0;
                while (cnt < tmp)
                {
                    q.emplace(resident[++pos]);
                    cnt++;
                }
            }
            else
            {
                ans += num * p;
                cout << ans << "\n";
                return;
            }
        }
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}