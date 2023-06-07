#include <stdio.h>

int main()
{
    int m, n;
    while (scanf("%d %d", &m, &n) != EOF)
    {
        // a+b=m;
        // 2*a+4*b=n;
        // b=(n-2*m)/2
        // a=(4*m-n)/2

        if (n % 2 != 0 || n - 2 * m < 0 || 4 * m - n < 0)
        {
            printf("-1 -1\n");
        }
        else
        {
            printf("%d %d\n", (4 * m - n) / 2, (n - 2 * m) / 2);
        }
    }
    return 0;
}