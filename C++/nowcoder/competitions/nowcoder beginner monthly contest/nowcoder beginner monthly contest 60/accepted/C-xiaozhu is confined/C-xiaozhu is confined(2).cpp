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
    for (int i = 1; i <= n; i++)
    {
        if (i <= k + 1)
        {
            dp[i] = a[i];
        }
        else
        {
            dp[i] = max(dp[i - 1], dp[i - k - 1] + a[i]);
        }
    }
    cout << dp[n] << endl;
    return 0;
}