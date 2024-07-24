#include <stdio.h>

int arr[100];

int main()
{
    int n;
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("%d\n", arr[(n - 1) / 2]);
    return 0;
}