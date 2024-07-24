#include <iostream>
using namespace std;

typedef long long ll;

int sort(const void *str2, const void *str1)
{
    return *((int *)str1) - *((int *)str2);
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        int a[300001];
        ll sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            sum += a[i];
        }
        qsort(a, n, sizeof(int), sort);
        ll left = 0;
        ll right = sum / m;
        ll ans = 0;
        while (left <= right)
        {
            int m1 = m;
            sum = 0;
            ll mid = (left + right) / 2;
            for (int i = 0; i < n; i++)
            {
                if (a[i] >= mid)
                {
                    m1--;
                    if (m1 <= 0)
                    {
                        ans = mid;
                        left = mid + 1;
                        break;
                    }
                }
                else
                {
                    for (int j = i; j < n; j++)
                    {
                        sum += a[j];
                    }
                    if (sum >= mid * m1)
                    {
                        ans = mid;
                        left = mid + 1;
                        break;
                    }
                    else
                    {
                        right = mid - 1;
                        break;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}