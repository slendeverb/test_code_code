#include <stdio.h>
#include <math.h>

double triangle_area(double a, double b, double c)
{
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main()
{
    double a, b, c;
    while (scanf("%lf %lf %lf", &a, &b, &c) != EOF)
    {
        double ans = triangle_area(a, b, c);
        printf("%.2lf\n", ans);
    }
    return 0;
}