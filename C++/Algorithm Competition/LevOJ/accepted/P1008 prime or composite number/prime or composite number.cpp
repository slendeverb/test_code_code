#include <stdio.h>
#include <math.h>

int is_prime(int n)
{
    if (n == 2 || n == 3)
    {
        return 1;
    }
    if (n % 6 != 1 && n % 6 != 5)
    {
        return 0;
    }
    int i;
    for (i = 5; i <= sqrt(n); i += 6)
    {
        if (n & i == 0 || n % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        if (is_prime(n))
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    return 0;
}