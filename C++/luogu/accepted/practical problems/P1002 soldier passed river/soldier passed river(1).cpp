#include <iostream>
using namespace std;
#include <vector>

int main()
{
    int n = 0, m = 0;
    int a = 0, b = 0;
    cin >> n >> m >> a >> b;
    vector<vector<long long int>> dp(n + 1, vector<long long int>(m + 1, 0));
    dp[a][b] = -1;
    dp[a - 2][b - 1] = -1;
    dp[a - 1][b - 2] = -1;
    dp[a - 2][b + 1] = -1;
    dp[a - 1][b + 2] = -1;
    dp[a + 1][b - 2] = -1;
    dp[a + 2][b - 1] = -1;
    dp[a + 1][b + 2] = -1;
    dp[a + 2][b + 1] = -1;
    int i = 0, j = 0;
    for (i = 0; i < n + 1 && dp[i][0] == 0; i++)
    {
        dp[i][0] = 1;
    }
    for (j = 1; j < m + 1 && dp[0][j] == 0; j++)
    {
        dp[0][j] = 1;
    }
    for (i = 1; i < n + 1; i++)
    {
        for (j = 1; j < m + 1; j++)
        {
            if (dp[i][j] == -1)
            {
                continue;
            }
            /*if(i==a,j==b)
            {
                dp[a+1][b+2]=0;
                dp[a+2][b+1]=0;
            }*/
            if (dp[i][j - 1] == -1)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else if (dp[i - 1][j] == -1)
            {
                dp[i][j] = dp[i][j - 1];
            }
            else
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
    long long ret = dp[n][m];
    cout << ret << endl;
    return 0;
}