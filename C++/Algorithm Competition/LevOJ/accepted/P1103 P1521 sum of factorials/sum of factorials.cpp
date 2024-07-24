#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int i = 0;
    int ret = 1;
    int sum = 0;
    for (i = 1; i <= n; i++)
    {
        ret *= i;
        sum += ret;
    }
    printf("%d\n", sum);
    return 0;
}