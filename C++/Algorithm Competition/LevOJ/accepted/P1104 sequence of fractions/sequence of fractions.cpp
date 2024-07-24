#include <stdio.h>

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int arr1[50] = {0};
        int arr2[50] = {0};
        arr1[0] = 1;
        arr1[1] = 2;
        arr2[0] = 2;
        arr2[1] = 3;
        int i = 0;
        for (i = 0; i < n; i++)
        {
            if (i >= 2)
            {
                arr1[i] = arr1[i - 1] + arr1[i - 2];
                arr2[i] = arr2[i - 1] + arr2[i - 2];
            }
        }
        if (n % 2 == 1)
        {
            printf("%d/%d\n", arr2[n - 1], arr1[n - 1]);
        }
        else
        {
            printf("-%d/%d\n", arr2[n - 1], arr1[n - 1]);
        }
    }
    return 0;
}