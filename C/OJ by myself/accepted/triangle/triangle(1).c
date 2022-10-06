#include <stdio.h>
#include <math.h>
int main()
{
    double a = 0.0, b = 0.0, c = 0.0;
    while (scanf("%lf %lf %lf", &a, &b, &c) != EOF)
    {
        int flag = 1;
        if (a <= 0 || b <= 0 || c <= 0)
        {
            printf("不构成三角形\n");
        }
        else
        {
            if (a + b > c && a + c > b && b + c > a)
            {
                if (a == b && b == c)
                {
                    printf("等边");
                    flag = 0;
                }
                else if (a == b || b == c || a == c)
                {
                    printf("等腰");
                    flag = 0;
                }
                if (fabs(a * a + b * b - c * c) < 10e-6 || fabs(a * a + c * c - b * b) < 10e-6 || fabs(b * b + c * c - a * a) < 10e-6)
                {
                    printf("直角");
                    flag = 0;
                }
                if (flag)
                {
                    printf("普通");
                }
                printf("三角形\n");
            }
            else
            {
                printf("不构成三角形\n");
            }
        }
    }
    return 0;
}
