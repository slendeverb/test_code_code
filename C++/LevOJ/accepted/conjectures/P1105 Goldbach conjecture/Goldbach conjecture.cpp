#include <iostream>
using namespace std;
#include <math.h>

int isprime(int p)
{
    if (p == 2 || p == 3)
    {
        return 1;
    }
    if (p % 6 != 1 && p % 6 != 5)
    {
        return 0;
    }
    int i = 0;
    for (i = 5; i <= floor(sqrt((double)p)); i += 6)
    {
        if (p % i == 0 || p % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int n = 0;
    int arr[10000] = {0};
    while (scanf("%d", &n) != EOF)
    {
        int i = 0;
        int tmp = 2;
        while (tmp < n)
        {
            if (isprime(tmp))
            {
                arr[i] = tmp;
                i++;
            }
            tmp++;
        }
        for (i = 0; i < n; i++)
        {
            if (isprime(n - arr[i]))
            {
                printf("%d+%d\n", arr[i], n - arr[i]);
                break;
            }
        }
    }
    return 0;
}