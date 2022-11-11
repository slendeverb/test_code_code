#include <iostream>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int a[2010] = {0};
    int dp[2010] = {0};
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i - k - 1 < 1)
        {
            dp[i] = a[i];
        }
        else
        {
            for (int j = 1; j <= i - k - 1; j++)
            {
                dp[i] = max(dp[i], a[i] + dp[j]);
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}