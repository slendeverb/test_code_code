#include <iostream>
using namespace std;
#include <math.h>

int isprime(int n)
{
    int i = 0;
    if (n == 2 || n == 3)
    {
        return 1;
    }
    if (n % 6 != 1 && n % 6 != 5)
    {
        return 0;
    }
    for (i = 5; i <= floor(sqrt((double)n)); i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int m = 0;
    int i = 0;
    while (scanf("%d", &m) != EOF)
    {
        for (i = m - 2; i >= 2; i--)
        {
            if (isprime(i) && isprime(i + 2))
            {
                printf("%d %d\n", i, i + 2);
                break;
            }
        }
    }
    return 0;
}