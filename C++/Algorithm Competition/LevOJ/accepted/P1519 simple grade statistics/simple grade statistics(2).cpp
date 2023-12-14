#include <stdio.h>
int find_max(int arr[], int sz)
{
    int i = 0;
    int tmp = arr[0];
    for (i = 0; i <= sz - 2; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            tmp = arr[i + 1];
        }
    }
    return tmp;
}
int find_min(int arr[], int sz)
{
    int i = 0;
    int tmp = arr[0];
    for (i = 0; i <= sz - 2; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            tmp = arr[i + 1];
        }
    }
    return tmp;
}
int main()
{
    int arr[100] = {0};
    double average = 0.0;
    int sum = 0;
    int count = 0;
    int i = 0;
    while (1)
    {
        scanf("%d", &arr[i]);
        if (arr[i] == -1)
        {
            break;
        }
        sum += arr[i];
        i++;
        count++;
    }
    int max = find_max(arr, i);
    int min = find_min(arr, i);
    average = (double)sum / count;
    printf("%d,%.2lf,%d,%d\n", count, average, max, min);
    return 0;
}