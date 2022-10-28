#include <iostream>
using namespace std;

int sort(const void *str1, const void *str2)
{
    return (*(int *)str1) - (*(int *)str2);
}
int main()
{
    long n = 0;
    long t = 0;
    long arr[50001] = {0};
    while (scanf("%ld %ld", &n, &t) != EOF)
    {
        long i = 0;
        for (i = 0; i < n; i++)
        {
            scanf("%ld", &arr[i]);
        }
        qsort(arr, n, sizeof(long), sort);
        for (i = 0; i < n && t > 0; i++)
        {
            t -= arr[i];
        }
        if (t < 0)
        {
            i--;
        }
        printf("%ld\n", i);
    }
    return 0;
}