#include <iostream>
using namespace std;
typedef unsigned long long ull;
int main()
{
    int t = 0;
    cin >> t;
    int i = 0;

    while (t--)
    {
        int n = 0;
        cin >> n;
        int *pa = new int[n + 1];
        int *pb = new int[n + 1];
        for (i = 0; i < n; i++)
        {
            cin >> pa[i];
        }
        for (i = 0; i < n; i++)
        {
            cin >> pb[i];
        }
        int left = pb[0];
        int right = pb[n - 1];
        for (i = 0; i < n; i++)
        {
            int j = 0;
            for (j = 0; j < n - 1 - i; j++)
            {
                if (pb[j] > pb[j + 1])
                {
                    int tmp = pb[j];
                    pb[j] = pb[j + 1];
                    pb[j + 1] = tmp;
                }
            }
        }
        ull sum = pa[n - 1];
        for (i = 0; i < n - 1; i++)
        {
            sum += pa[i];
            sum += (2 * pb[i]);
        }
        int max = left > right ? left : right;
        if (n >= 3)
        {
            sum = sum - left - right;
        }
        else
        {
            sum -= max;
        }
        free(pa);
        pa = NULL;
        free(pb);
        pb = NULL;
        cout << sum << endl;
    }
    return 0;
}