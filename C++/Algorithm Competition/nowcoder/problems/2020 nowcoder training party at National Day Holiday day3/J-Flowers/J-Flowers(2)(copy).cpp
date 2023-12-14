#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 4e5 + 8;
typedef long long ll;
ll a[maxn];

int n, m;
bool check(ll x) // x束花
{
    ll tot = 0;
    for (int i = 1; i <= n; i++)
        tot += min(a[i], x);
    if (tot >= x * m)
        return 1;
    return 0;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        ll sum = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            sum += a[i];
        }
        ll l = 0, r = sum / m, ans;
        while (l <= r)
        {
            ll mid = (l + r) >> 1;
            if (check(mid))
            {
                l = mid + 1;
                ans = mid;
            }
            else
                r = mid - 1;
        }
        cout << ans << endl;
    }
    return 0;
}