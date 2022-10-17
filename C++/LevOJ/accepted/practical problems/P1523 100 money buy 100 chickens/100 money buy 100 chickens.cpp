#include <stdio.h>

int main()
{
    int x = 0;
    scanf("%d", &x);
    double a = 0.0, b = 0.0, c = 0.0;
    for (a = 0; a < x / 5; a++)
    {
        for (b = 0; b < x / 3; b++)
        {
            for (c = 0; c < x * 2; c++)
            {
                if ((a > 0 && b > 0 && c > 0) && (a + b + c == x) && (5 * a + 3 * b + 0.5 * c == x))
                {
                    printf("%.0lf %.0lf %.0lf\n", a, b, c);
                }
            }
        }
    }
    return 0;
}