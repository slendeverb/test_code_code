#include <stdio.h>

int main()
{
    unsigned long long int arr[100] = {0};
    arr[0] = 1, arr[1] = 1;
    int i = 0;
    for (i = 2; i < 100; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    int n = 0;
    scanf("%d", &n);
    int count = 0;
    for (i = 0; i < n; i++)
    {
        printf("%12d", arr[i]);
        count++;
        if (count == 4)
        {
            printf("\n");
            count = 0;
        }
    }
    return 0;
}