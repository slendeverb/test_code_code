#include <iostream>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    int i = 0, j = 0, k = 0;
    for (i = 0; i < t; i++)
    {
        int n = 0;
        cin >> n;
        int arr[51] = {0};
        for (j = 1; j <= n; j++)
        {
            arr[j] = j;
        }
        int flag = 1;
        for (k = 0; k < 10000; k++)
        {
            for (j = 1; j <= n; j++)
            {
                if (n - j > 3)
                {
                    if (arr[j] - arr[j + 1] == 1 || arr[j] - arr[j + 1] == -1 && flag)
                    {
                        int tmp = arr[j];
                        arr[j] = arr[j + 3];
                        arr[j + 3] = tmp;
                        flag = 0;
                    }
                    if (arr[j] - arr[j + 1] == 1 || arr[j] - arr[j + 1] == -1 && flag == 0)
                    {
                        int tmp = arr[j];
                        arr[j] = arr[j - 1];
                        arr[j - 1] = tmp;
                        flag = 1;
                    }
                }
                else
                {
                    if (arr[j] - arr[j + 1] == 1 || arr[j] - arr[j + 1] == -1)
                    {
                        int tmp = arr[j];
                        arr[j] = arr[1];
                        arr[1] = tmp;
                    }
                }
            }
        }
        for (j = 1; j <= n; j++)
        {
            printf("%d ", arr[j]);
        }
        cout << endl;
    }
    return 0;
}