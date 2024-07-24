#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;
    int ma = max(a, max(b, c));
    int mi = min(a, min(b, c));
    int ans = ma ^ mi ^ a ^ b ^ c;
    cout<<ans<<"\n";
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