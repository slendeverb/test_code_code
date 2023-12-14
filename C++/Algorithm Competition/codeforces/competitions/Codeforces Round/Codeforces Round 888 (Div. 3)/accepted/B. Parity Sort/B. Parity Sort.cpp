#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 2e5 + 10;

int a[maxn], b[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int odd = 0, even = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            b[i] = a[i];
            if (a[i] % 2 == 0)
            {
                even++;
            }
            else
            {
                odd++;
            }
        }
        if (even == 0 || odd == 0 || n == 1)
        {
            cout << "YES\n";
        }
        else
        {
            sort(b + 1, b + 1 + n);
            int flag = 1;
            for (int i = 1; i <= n; i++)
            {
                if (b[i] % 2 == 1 && a[i] % 2 == 0)
                {
                    flag = 0;
                    break;
                }
                if (b[i] % 2 == 0 && a[i] % 2 == 1)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
    return 0;
}