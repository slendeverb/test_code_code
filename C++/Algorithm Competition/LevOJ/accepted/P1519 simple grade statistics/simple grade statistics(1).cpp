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
float Average(int arr[], int sz)
{
    int sum = 0;
    int i = 0;
    for (i = 0; i <= sz - 1; i++)
    {
        sum += arr[i];
    }
    float ret = (float)sum / sz;
    return ret;
}

int main()
{
    int arr[100] = {0};
    int i = 0;
    char ch = 0;
    for (i = 0; arr[i - 1] != -1; i++)
    {
        scanf("%d", &arr[i]);
        ch = getchar();
        if (ch == '\n')
        {
            break;
        }
    }
    if (arr[i - 1] == -1)
    {
        i = i - 1;
    }
    int sz = i;
    int max = find_max(arr, sz);
    int min = find_min(arr, sz);
    float average = Average(arr, sz);
    printf("%d,%.2f,%d,%d\n", i, average, max, min);
    return 0;
}