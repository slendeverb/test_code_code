#include <iostream>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        long long ans = 0;
        int num_50 = n / 50;
        ans += num_50 * 5 + num_50 * 2;
        n -= num_50 * 50;
        if (n > 0)
        {
            int num_30 = n / 30;
            ans += num_30 * 3 + num_30 * 1;
            n -= num_30 * 30;
            if (n > 0)
            {
                int num_10 = n / 10;
                ans += num_10 * 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}