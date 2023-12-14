#include <iostream>
using namespace std;

int main()
{
    long n = 0;
    long i = 0, j = 0;
    while (scanf("%ld", &n) != EOF)
    {
        long sum = 0;
        for (i = 0; i < n; i++)
        {
            long k = 0;
            scanf("%ld", &k);
            long max = 0;
            long t = 0;
            for (j = 0; j < k; j++)
            {
                scanf("%ld", &t);
                max = (max > t ? max : t);
            }
            sum += max;
        }
        printf("%ld\n", sum);
    }
    return 0;
}