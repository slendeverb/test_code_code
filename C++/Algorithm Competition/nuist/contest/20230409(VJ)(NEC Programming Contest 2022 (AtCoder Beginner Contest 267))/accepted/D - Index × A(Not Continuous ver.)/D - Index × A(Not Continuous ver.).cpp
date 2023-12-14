#include <iostream>
#include <climits>
using namespace std;

const int maxn = 2010;
long long a[maxn];
long long dp[maxn][maxn];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    dp[0][1] = LLONG_MIN;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j > i)
            {
                dp[i][j] = LLONG_MIN;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j - 1] + j * a[i], dp[i - 1][j]);
            }
        }
    }
    cout << dp[n][m] << "\n";
    return 0;
}