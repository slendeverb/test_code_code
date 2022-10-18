#include <iostream>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    int i = 0, j = 0;
    for (i = 0; i < t; i++)
    {
        int n = 0;
        cin >> n;
        int arr[10] = {0};
        int tmp1 = 1;
        int tmp2 = 1;
        for (j = 0; j < n; j++)
        {
            cin >> arr[j];
        }
        for (j = 1; j <= 10 - n; j++)
        {
            tmp1 *= j;
        }
        for (j = 1; j <= 10 - 2 - n; j++)
        {
            tmp2 *= j;
        }
        cout << (tmp1 / (tmp2 * 2)) * 6 << endl; // 2C4*2C(10-n)
    }
    return 0;
}