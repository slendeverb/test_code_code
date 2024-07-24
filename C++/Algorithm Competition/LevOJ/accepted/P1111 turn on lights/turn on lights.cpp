#include <iostream>
using namespace std;

int main()
{
    int n = 0, k = 0;
    while (scanf("%d %d", &n, &k) != EOF)
    {
        int i = 0;
        int *p = new int[n + 1];
        for (i = 1; i <= n; i++)
        {
            p[i] = 1;
        }
        i = 2;
        while (i <= k)
        {
            int j = 0;
            for (j = i; j <= n; j += i)
            {
                p[j] = (p[j] == 1 ? 0 : 1);
            }
            i++;
        }
        for (i = 1; i <= n; i++)
        {
            if (p[i] == 1)
            {
                cout << i << endl;
            }
        }
    }
    return 0;
}