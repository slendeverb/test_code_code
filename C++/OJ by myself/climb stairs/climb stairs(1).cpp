#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    int t = 0;
    scanf("%d", &t);
    int i = 0, j = 0, k = 0;
    int m = 0, n = 0;
    int arr[100001] = {0};
restart:
    for (; i < t; i++)
    {
        scanf("%d", &m);
        scanf("%d", &n);
        for (j = 0; j < n; j++)
        {
            scanf("%d", &arr[j]);
        }
        int step = 0;
        int sum = 0;
        int max = m;
        int b = 1;
        int n1 = n;
        int m1 = m;
        for (k = 0; k < 1000000; k++)
        {
            sum = 0;
            n1 = n;
            m1 = m;
            for (j = 0; j < n; j++)
            {
                int tmp = 0;
                tmp = rand() % 2 + 1;
                n1 -= tmp;
                sum += tmp;
                m1 -= arr[sum - 1];
                if (n1 <= 0)
                {
                    break;
                }
            }
            if (n1 == 0 && m1 >= 0)
            {
                if (b)
                {
                    max = m1;
                    b = 0;
                }
                if (max < m1)
                {
                    max = m1;
                }
                printf("%d\n", max);
                if (i < t)
                {
                    i++;
                    goto restart;
                }
            }
        }
        if (n1 < 0 || m1 <= 0)
        {
            printf("Can't get the top!\n");
        }
    }
    return 0;
}