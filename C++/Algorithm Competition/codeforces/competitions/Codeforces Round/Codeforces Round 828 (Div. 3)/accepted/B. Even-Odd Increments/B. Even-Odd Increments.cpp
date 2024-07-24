#include <iostream>
using namespace std;
typedef long long ll;
int main()
{
    ll t = 0;
    cin >> t;
    while (t--)
    {
        ll n = 0, q = 0;
        cin >> n >> q;
        ll a[100010] = {0};
        int type = 0;
        ll x = 0;
        ll sum = 0;
        ll count_odd = 0;
        ll count_even = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            if (a[i] % 2 == 0)
            {
                sum += a[i];
                count_even++;
            }
            else
            {
                sum += a[i];
                count_odd++;
            }
        }
        for (int i = 0; i < q; i++)
        {
            cin >> type;
            cin >> x;
            if (type == 0)
            {
                sum += count_even * x;
            }
            else
            {
                sum += count_odd * x;
            }
            if (x % 2 != 0)
            {
                if (type != 0)
                {
                    count_even = count_even + count_odd;
                    count_odd = 0;
                }
                else
                {
                    count_odd = count_even + count_odd;
                    count_even = 0;
                }
            }
            printf("%lld\n", sum);
        }
    }
    return 0;
}