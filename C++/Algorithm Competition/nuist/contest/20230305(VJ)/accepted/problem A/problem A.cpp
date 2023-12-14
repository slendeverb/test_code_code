#include <iostream>
using namespace std;

const int N = 110;
int n, m;
int a[N];
const int mod = 1e6 + 7;
long long ans;
long long dp[N][N];
// dp[i][j]表示用i种花摆j个花盆的方案数

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int k = 0; k <= a[i]; k++)
            {
                if (j - k < 0)
                {
                    break;
                }
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % mod;
            }
        }
    }
    cout << dp[n][m] << "\n";
    return 0;
}