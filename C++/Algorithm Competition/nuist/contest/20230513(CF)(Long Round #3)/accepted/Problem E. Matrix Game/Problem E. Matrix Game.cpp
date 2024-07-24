#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 505;
const int maxx = 1005;
char a[maxn][maxn];
int dp[2][maxn][maxx];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, x;
        cin >> n >> m >> x;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> a[i][j];
            }
        }
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                for (int k = 0; k <= x; k++)
                {
                    dp[i][j][k] = 0;
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                for (int k = 0; k <= x; k++)
                {
                    if (a[i][j] == '0')
                    {
                        dp[i & 1][j][k] = max(dp[(i - 1) & 1][j][k], dp[i & 1][j - 1][k]);
                    }
                    else if (a[i][j] == '1')
                    {
                        dp[i & 1][j][k] = max(dp[(i - 1) & 1][j][k], dp[i & 1][j - 1][k]) + 1;
                    }
                    else
                    {
                        if (k > 0)
                        {
                            dp[i & 1][j][k] = max(dp[(i - 1) & 1][j][k - 1], dp[i & 1][j - 1][k - 1]) + 1;
                        }
                        else
                        {
                            dp[i & 1][j][k] = max(dp[(i - 1) & 1][j][k], dp[i & 1][j - 1][k]);
                        }
                    }
                }
            }
        }
        cout << dp[n & 1][m][x] << "\n";
    }
    return 0;
}