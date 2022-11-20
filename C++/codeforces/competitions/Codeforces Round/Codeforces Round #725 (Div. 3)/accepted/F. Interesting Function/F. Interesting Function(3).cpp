#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve()
{
    int l, r;
    cin >> l >> r;
    int ans = 0;
    while (l || r)
    {
        ans += r - l;
        l /= 10;
        r /= 10;
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}