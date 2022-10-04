#include <stdio.h>

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int ret = 1;
        int sum = 1;
        if (n > 0)
        {
            int i = 0;
            for (i = 1; i <= n; i++)
            {
                ret *= i;
                sum += ret;
            }
        }
        else
        {
            sum = 1;
        }
        printf("%d\n", sum);
    }
    return 0;
}