#include <stdio.h>
int main()
{
    int i = 0;
    int n = 0;
    scanf("%d", &n);
    unsigned int a = 0, b = 0;
    char ch = 0;
    while (n-- && scanf("%u%c%u", &a, &ch, &b))
    {
        if (ch == '+')
        {
            printf("%u\n", a + b);
        }
        else if (ch == '-')
        {
            if (a > b)
            {
                printf("%u\n", a - b);
            }
            else if (a < b)
            {
                printf("-%u\n", b - a);
            }
            else
            {
                printf("%d\n", 0);
            }
        }
        else if (ch == '*')
        {
            printf("%u\n", a * b);
        }
        else if (ch == '/')
        {
            printf("%u\n", a / b);
        }
    }
    return 0;
}