#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int k;
    cin >> k;
    while (k--)
    {
        long long n;
        cin >> n;
        long long i;
        for (i = 1; i <= n; i++)
        {
            if (n > i * (i - 1) / 2 && n <= i * (i + 1) / 2)
            {
                break;
            }
        }
        int pos = n - (i * (i - 1) / 2);
        int ans = 0;
        if (pos % 9 == 0)
        {
            ans = 9;
        }
        else
        {
            ans = pos % 9;
        }
        cout << ans << "\n";
    }
    return 0;
}