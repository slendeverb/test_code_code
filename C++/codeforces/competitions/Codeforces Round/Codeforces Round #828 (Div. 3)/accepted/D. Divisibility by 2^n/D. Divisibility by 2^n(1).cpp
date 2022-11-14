#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0;
        cin >> n;
        int arr[200010] = {0};
        long long multi = 1;
        int ret1 = 0, ret2 = 0;
        int x = (int)pow(2, n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            multi *= arr[i];
        }
        if (multi % x == 0)
        {
            cout << 0 << "\n";
        }
        else
        {
            int p = 1;
            for (int i = 1; i <= n; i++)
            {
                p *= i;
            }
            if ((multi * p) % x != 0)
            {
                cout << -1 << "\n";
            }
            else
            {
                multi = multi * p;
                for (int i = n; i >= 2; i--)
                {
                    
                }
            }
        }
    }
    return 0;
}