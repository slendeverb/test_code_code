#include <iostream>
#include <climits>
using namespace std;

typedef long long ll;

const int N = 5e5 + 10;
ll v[N];
ll t, n, m, k, num, start = -1, maxx, cnt = LLONG_MAX, t1;

void solve()
{
    for (int i = start; i < t; i++)
    {
        num += v[i];
        if (num >= k)
        {
            num -= k;
        }
        else
        {
            num = 0;
        }
    }
    if (num != n)
    {
        cout << "Wrong Record"
             << "\n";
        return;
    }
    else
    {
        for (int i = maxx; i > t; i--)
        {
            num += v[i];
            if (num >= k)
            {
                num -= k;
            }
            else
            {
                num = 0;
            }
            ll num1 = num + 1;
            ll tmp1 = num1 % k;
            ll tmp2 = num1 / k;
            if (tmp1 == 0)
            {
                if (cnt > tmp2)
                {
                    cnt = tmp2;
                    t1 = i;
                }
            }
            else
            {
                if (cnt > tmp2 + 1)
                {
                    cnt = tmp2 + 1;
                    t1 = i;
                }
            }
        }
        cout << t1 << " " << cnt << "\n";
    }
}

int main()
{
    cin >> t >> n >> m >> k;
    v[t] = n;
    while (m--)
    {
        ll ti, xi;
        cin >> ti >> xi;
        if (start == -1)
        {
            start = ti;
        }
        maxx = max(ti, maxx);
        v[ti] = xi;
    }
    solve();
    return 0;
}