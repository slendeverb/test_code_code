#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 105;
int y1, y2;
int n;
int s[N];

void solve()
{
    cin >> y1;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    cin >> y2;
    int ans = y2 - y1 + 1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] >= y1 && s[i] <= y2)
        {
            ans--;
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