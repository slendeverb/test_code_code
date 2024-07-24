#include <bits/stdc++.h>
using namespace std;

int n, m;

struct node
{
    int x, y, l;
};

void solve()
{
    cin >> n >> m;
    if (n == m)
    {
        cout << "YES" << '\n';
        cout << "1\n";
        cout << "0 0 " << n << "\n";
    }
    else
    {
        vector<node> v;
        int x = 0, y = 0;
        while (n != m)
        {
            if (n < m)
            {
                v.push_back({x, y, n});
                m -= n;
                y += n;
            }
            else
            {
                v.push_back({x, y, m});
                n -= m;
                x += m;
            }
        }
        v.push_back({x, y, n});
        cout << "YES" << '\n';
        cout << v.size() << "\n";
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i].x << " " << v[i].y << " " << v[i].l << "\n";
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}