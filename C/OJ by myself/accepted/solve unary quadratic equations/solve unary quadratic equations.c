#include <stdio.h>
#include <math.h>
int main()
{
    double a = 0.0, b = 0.0, c = 0.0;
    while (scanf("%lf %lf %lf", &a, &b, &c) != EOF)
    {
        if (a == 0)
        {
            printf("不是一元二次方程\n");
        }
        else if (b * b - 4 * a * c >= 0)
        {
            double solve1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
            double solve2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
            printf("%.2lf %.2lf\n", solve1, solve2);
        }
        else if (b * b - 4 * a * c < 0)
        {
            double imaginary_solve1 = -b / (2 * a);
            double imaginary_solve2 = sqrt(fabs(b * b - 4 * a * c)) / (2 * a);
            printf("%.2lf+%.2lfi", imaginary_solve1, imaginary_solve2);
            printf(" %.2lf-%.2lfi\n", imaginary_solve1, imaginary_solve2);
        }
    }
    return 0;
}