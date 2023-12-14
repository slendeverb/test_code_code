#include <iostream>
#include <cmath>
using namespace std;

int t, n;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        long long sum = 0, ans = 0, maxx = -1;
        for (int i = 0; i < n; i++)
        {
            long long x;
            cin >> x;
            maxx = max(maxx, x);
            sum += x;
        }
        ans = (long long)ceil((double)sum / (n - 1));
        ans = max(maxx, ans);
        ans = ans * (n - 1) - sum;
        cout << ans << "\n";
    }
    return 0;
}