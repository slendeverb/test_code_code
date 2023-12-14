#include <stdio.h>

int arr[1001];

void bubble_sort(int arr[], int n)
{
    int i, j;
    int tmp;
    for (i = 0; i < n - 1; i++)
    {
        int sort_flag = 0;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                sort_flag = 1;
            }
        }
        if (!sort_flag)
        {
            return;
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    bubble_sort(arr, n);
    printf("%d", arr[0]);
    for (i = 1; i < n; i++)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
    return 0;
}