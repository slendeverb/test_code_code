#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        long long ans = 0;
        if (n == 1 || m == 1)
        {
            if (n == 1 && m == 1)
            {
                ans = 1;
            }
            else if (n == 1)
            {
                ans = ceil(m / 2.0);
            }
            else
            {
                ans = ceil(n / 2.0);
            }
        }
        else
        {
            if (n % 3 == 0 || m % 3 == 0)
            {
                ans = 2;
            }
            else
            {
                ans = 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}