#include <iostream>
using namespace std;
#include <cstring>
int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0;
        cin >> n;
        int i = 0;
        int min = 10000;
        int *pa = new int[n + 1];
        memset(pa, 0, n + 1);
        for (i = 1; i <= n; i++)
        {
            cin >> pa[i];
            if (min > pa[i])
            {
                min = pa[i];
            }
        }
        int k = 0;
        int m = 0;
        int flag = 0, flag2 = 0;
        if (min > 1)
        {
            goto End;
        }

        k = 1;
        while (1)
        {
            i = 0;
            do
            {
                flag = 0;
                i++;
                int x = k - i + 1;
                int max = 0;
                int a = 0;
                int max2 = 0, a2 = 0;
                for (m = 1; m <= n - i + 1; m++)
                {
                    if (pa[m] <= x && pa[m] != 0)
                    {
                        flag = 1;
                        if (pa[m] > max)
                        {
                            max = pa[m];
                            a = i;
                        }
                    }
                }
                int j = 0;
                for (j = a; j <= n - i; j++)
                {
                    pa[j] = pa[j + 1];
                }
                for (j = 1; j <= n - i; j++)
                {
                    if (pa[j] > max2 && pa[j] != 0)
                    {
                        a2 = j;
                    }
                }
                if (n - i >= 1)
                {
                    pa[a2] += x;
                }
            } while (flag && i <= k);
            if (i > k)
            {
                k++;
                if (k > n)
                {
                    k--;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    End:
        cout << k << endl;
    }
    return 0;
}