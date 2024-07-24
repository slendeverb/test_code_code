#include <iostream>
using namespace std;

void sort_max(int arr[], int sz)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < sz - 1; i++)
    {
        int flag = 1;
        for (j = 0; j < sz - 1 - i; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = 0;
            }
        }
        if (flag)
        {
            break;
        }
    }
}
void sort_min(int arr[], int sz)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < sz - 1; i++)
    {
        int flag = 1;
        for (j = 0; j < sz - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                flag = 0;
            }
        }
        if (flag)
        {
            break;
        }
    }
}
int main()
{
    int a = 0;
    while (scanf("%d", &a) != EOF)
    {
        if (a == 6174)
        {
            cout << 0 << endl;
        }
        else
        {
            int count = 0;
            int i = 0;
            int arr[4] = {0};
            int arr1[4] = {0};
            int arr2[4] = {0};
            while (1)
            {
                for (i = 0; i < 4; i++)
                {
                    arr[i] = a % 10;
                    arr1[i] = arr[i];
                    arr2[i] = arr[i];
                    a /= 10;
                }
                int sz = sizeof(arr) / sizeof(arr[0]);
                sort_max(arr1, sz);
                sort_min(arr2, sz);
                int a1 = 0;
                int a2 = 0;
                for (i = 0; i < 4; i++)
                {
                    a1 = a1 * 10 + arr1[i];
                    a2 = a2 * 10 + arr2[i];
                }
                count++;
                if ((a1 - a2) == 6174)
                {
                    cout << count << endl;
                    break;
                }
                else
                {
                    a = a1 - a2;
                }
            }
        }
    }
    return 0;
}