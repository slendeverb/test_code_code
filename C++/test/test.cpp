#include <stdio.h>

int main()
{
    int t = 0;
    scanf("%d", &t);
    unsigned long long int rabit[100001] = {0};
    rabit[0] = 1;
    rabit[1] = 1;
    int trap[100001] = {0};
    int arr[100001] = {0};
    int i = 0;
    int k = 0;
    unsigned long long int j = 0;
    int m = 0, n = 0;
    int max = 0;
    int n1=n,m1=m;
    for (i = 0; i < 100001; i++)
    {
        arr[i] = 1;
    }
    for (i = 0; i < t; i++)
    {
        scanf("%d", &m);
        scanf("%d", &n);
        for (j = 2; j <= n; j++)
        {
            rabit[j] = rabit[j - 1] + rabit[j - 2];
        }
        for (j = 0; j < n; j++)
        {
            scanf("%d", trap[j]);
        }
        for (j = 1; j <= rabit[n]; j++)
        {
            for (k = 0; k <= n; k++)
            {
                arr[k] = 2;
                if (k >= 1)
                {
                    arr[k - 1] = 1;
                }
            }
        }
    }
    return 0;
}