#include <stdio.h>

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        if (n % 7 == 0)
        {
            printf("%d\n", 7);
        }
        else
        {
            printf("%d\n", n % 7);
        }
    }
    return 0;
}