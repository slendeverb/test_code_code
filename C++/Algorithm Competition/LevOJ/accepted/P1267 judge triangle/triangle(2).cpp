#include <stdio.h>
int main()
{
    int a = 0, b = 0, c = 0;
    while (scanf("%d %d %d", &a, &b, &c) != EOF)
    {
        int flag = 1;
        if (a + b > c && a + c > b && b + c > a)
        {
            if (a == b && b == c)
            {
                printf("regular triangle\n");
                flag = 0;
            }
            else if (a == b || b == c || a == c)
            {
                printf("isosceles triangle\n");
                flag = 0;
            }
            else if (a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a)
            {
                printf("right triangle\n");
                flag = 0;
            }
            if (flag)
            {
                printf("triangle\n");
            }
        }
        else
        {
            printf("not a triangle\n");
        }
    }
    return 0;
}
