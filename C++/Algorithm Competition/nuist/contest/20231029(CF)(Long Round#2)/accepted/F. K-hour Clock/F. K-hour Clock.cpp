#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

int x, y, z;

void solve()
{
    cin >> x >> y >> z;
    int d = x + y - z;
    if (d <= max(x, z) && d != 0)
    {
        cout << "-1\n";
    }
    else if (d == 0)
    {
        cout << z + 1 << endl;
    }
    else
    {
        cout << d << endl;
    }
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