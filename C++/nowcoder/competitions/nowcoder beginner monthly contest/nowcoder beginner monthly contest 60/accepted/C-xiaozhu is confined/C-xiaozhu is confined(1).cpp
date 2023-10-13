#include <iostream>
using namespace std;

typedef struct A
{
    int num;
    int x;
} A;

void sort(A arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int count = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j].num < arr[j + 1].num)
            {
                A tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                count++;
            }
        }
        if (count == 0)
        {
            return;
        }
    }
}
int main()
{
    int n, k;
    cin >> n >> k;
    A arr[4001] = {0};
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i].num;
        arr[i].x = i;
    }
    sort(arr, n);
    int ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i].num > 0)
        {
            ans += arr[i].num;
        }
        if (arr[i + 1].x >= arr[i].x + 1 && arr[i + 1].x <= arr[i].x + k)
        {
            arr[i + 1].num = 0;
        }
    }
    cout << ans << endl;
    return 0;
}