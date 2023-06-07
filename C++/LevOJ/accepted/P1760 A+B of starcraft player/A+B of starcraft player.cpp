#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int a = 0, b = 0;
    int arr[1000] = {0};
    int i = 0;
    int j = 0;
    for (i = 2; i < 1000; i++)
    {
        int flag = 1;
        for (j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                flag = 0;
            }
        }
        if (flag)
        {
            arr[i] = i;
        }
    }
    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 1000; j++)
        {
            if (n == arr[i] * arr[j])
            {
                cout << arr[i] + arr[j] << endl;
                goto End;
            }
        }
    }
End:
    return 0;
}