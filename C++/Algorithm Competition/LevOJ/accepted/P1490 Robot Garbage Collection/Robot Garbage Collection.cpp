#include <iostream>
using namespace std;

const int maxn = 210;
int dp[maxn][maxn];

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> dp[i][j];
            }
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = max(dp[i][j] + dp[i - 1][j], dp[i][j] + dp[i][j - 1]);
            }
        }

        cout << dp[n][m] << "\n";
    }
    return 0;
}