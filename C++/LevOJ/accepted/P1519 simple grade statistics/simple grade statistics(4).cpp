#include <stdio.h>

int main()
{
    int max = 0;
    int min = 10000;
    int a = 0;
    int i = 0;
    int sum = 1;//为什么sum要初始化成1，因为最后一步有a=-1要加到sum上
    double average = 0.0;
    for (i = 0; a != -1; i++)
    {
        scanf("%d", &a);
        sum += a;
        if (a < min && a != -1)
        {
            min = a;
        }
        if (a > max && a != -1)
        {
            max = a;
        }
    }
    average = (double)sum / (i - 1);
    printf("%d,%.2lf,%d,%d\n", i - 1, average, max, min);
    return 0;
}