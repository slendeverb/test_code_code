#include <iostream>
using namespace std;

int sort(const void *str1, const void *str2)
{
    return *((int *)str1) - *((int *)str2);
}
int main()
{
    int n = 0;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    qsort(arr, n, sizeof(int), sort);
    int sum_Alice = 0;
    int sum_Bob = 0;
    if (n % 2 == 0)
    {
        for (int i = n - 1; i >= 1; i -= 2)
        {
            sum_Alice += arr[i];
        }
        for (int i = n - 2; i >= 0; i -= 2)
        {
            sum_Bob += arr[i];
        }
    }
    else
    {
        for (int i = n - 1; i >= 0; i -= 2)
        {
            sum_Alice += arr[i];
        }
        for (int i = n - 2; i >= 1; i -= 2)
        {
            sum_Bob += arr[i];
        }
    }
    cout << sum_Alice - sum_Bob << endl;
    return 0;
}