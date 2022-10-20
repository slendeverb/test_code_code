#include <iostream>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    int i = 0, j = 0;
    int max = 0, min = 2000000;
    for (i = 0; i < t; i++)
    {
        int n = 0;
        cin >> n;
        int arr1[10000] = {0};
        int arr2[10000] = {0};
        for (j = 1; j <= n; j++)
        {
            scanf("%1d", &arr1[j]);
        }
        for (j = 1; j <= n; j++)
        {
            int tmp = 0;
            cin >> tmp;
            arr2[j] = tmp;
            if (tmp > max)
            {
                max = tmp;
            }
            if (tmp < min)
            {
                min = tmp;
            }
        }
        for (j = 1; j <= n; j++)
        {
            if (arr2[j - 1] > arr2[j] && arr1[j] == 1)
            {
                arr1[j - 1] += 1;
                arr1[j] -= 1;
            }
            if (arr1[j - 1] == 2)
            {
                arr1[j - 2] += 1;
                arr1[j - 1] -= 1;
            }
        }
        int sum = 0;
        for (j = 1; j <= n; j++)
        {
            if (arr1[j] == 1)
            {
                sum += arr2[j];
            }
        }
        cout << sum << endl;
    }
    return 0;
}