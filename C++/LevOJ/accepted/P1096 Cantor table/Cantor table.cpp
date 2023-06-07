#include <stdio.h>

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        int k = 0;
        while (k * (k + 1) / 2 < n)
        {
            k++;
        }
        int num = (k * (k + 1) / 2) - n;
        if (k % 2 == 0)
        {
            printf("%d/%d\n", k - num, 1 + num);
        }
        else
        {
            printf("%d/%d\n", 1 + num, k - num);
        }
    }
    return 0;
}