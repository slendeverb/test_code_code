#include <bits/stdc++.h>
using namespace std;

int ans = 0;

void dfs(int x, int y, int step)
{
    if (x == y)
    {
        ans = step;
        return;
    }
    if (x > y)
    {
        if (x % 6 == 0)
        {
            dfs(x / 6, y, step + 1);
        }
        else
        {
            ans = -1;
            return;
        }
    }
    else if (x < y)
    {
        dfs(x * 5, y, step + 1);
    }
}

void solve()
{
    int x, y;
    cin >> x >> y;
    dfs(x, y, 0);
    cout << ans << "\n";
}

int main()
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