// 1519简单成绩统计
#include <stdio.h>
int main()
{
    double n, min = 10000.0, max = 0.0, s = 0.0, sum = 1.0, av = 0.0;
    for (n = 0; s != -1; n++)
    {
        scanf("%lf", &s);
        sum = s + sum;
        if (s < min && s != -1)
        {
            min = s;
        }
        if (s > max && s != -1)
        {
            max = s;
        }
    }
    av = sum / (n - 1);
    printf("%.0lf,%.2lf,%.0lf,%.0lf\n", (n - 1), av, max, min);
    return 0;
}