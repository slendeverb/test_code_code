#include <iostream>
using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int t = 0;
    cin >> t;
    while (t--)
    {
        ll n, m;
        cin >> n >> m;
        ll sum = 0;
        ll a[300001];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            sum += a[i];
        }
        ll l = 0;
        ll r = sum / m;
        ll ans = 0;
        while (l <= r)
        {
            ll mid = (l + r) / 2;
            ll tmp = 0;
            for (int i = 0; i < n; i++)
            {
                tmp += min(a[i], mid);
            }
            if (tmp >= mid * m)
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}