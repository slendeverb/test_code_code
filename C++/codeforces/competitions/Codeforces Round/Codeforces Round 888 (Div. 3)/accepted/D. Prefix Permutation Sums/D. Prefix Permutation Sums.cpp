#include <iostream>
#include <map>
using namespace std;

const int maxn = 2e5 + 10;

long long a[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        map<long, long> m;
        for (int i = 1; i <= n - 1; i++)
        {
            cin >> a[i];
        }
        int flag1 = 1;
        int lost = 0;
        m[1]++;
        m[a[1] - 1]++;
        for (int i = 2; i <= n - 1; i++)
        {
            m[a[i] - a[i - 1]]++;
        }
        for (int i = 1; i <= n; i++)
        {
            if (m.count(i))
            {
                if (m[i] > 1)
                {
                    flag1 = 0;
                    break;
                }
            }
            else
            {
                lost++;
                if (lost > 0)
                {
                    flag1 = 0;
                    break;
                }
            }
        }

        int flag2 = 1;
        lost = 0;
        m.clear();
        m[a[1]]++;
        for (int i = 2; i <= n - 1; i++)
        {
            m[a[i] - a[i - 1]]++;
        }
        for (int i = 1; i <= n; i++)
        {
            if (m.count(i))
            {
                if (m[i] > 1)
                {
                    flag2 = 0;
                    break;
                }
            }
            else
            {
                lost++;
                if (lost > 1)
                {
                    flag2 = 0;
                    break;
                }
            }
        }

        int flag3 = 1;
        lost = 0;
        long long sum = 0;
        for (int i = 1; i <= n; i++)
        {
            if (m.count(i))
            {
                if (m[i] > 2)
                {
                    flag3 = 0;
                    break;
                }
            }
            else
            {
                sum += i;
                lost++;
                if (lost > 2)
                {
                    flag3 = 0;
                    break;
                }
            }
        }
        if (flag3 && ((sum > n && m[sum] != 1) || (sum <= n && m[sum] != 2)))
        {
            flag3 = 0;
        }

        if (flag1 || flag2 || flag3)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
    return 0;
}