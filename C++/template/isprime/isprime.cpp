#include <cmath>

int isprime(int num)
{
    if (num == 1)
    {
        return 0;
    }
    if (num == 2 || num == 3)
    {
        return 1;
    }
    if (num % 6 != 1 && num % 6 != 5)
    {
        return 0;
    }
    for (int i = 5; i <= floor(sqrt((double)num)); i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}