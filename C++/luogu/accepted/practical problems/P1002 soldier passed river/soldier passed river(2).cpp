#include <iostream>
using namespace std;
#include <vector>
int main()
{
    int n = 0, m = 0;
    int a = 0, b = 0;
    cin >> n >> m >> a >> b;
    vector<vector<long long int>> dp(n + 5, vector<long long int>(m + 5, 0));
    vector<vector<bool>> t(n + 5, vector<bool>(m + 5, true));
    t[a + 2][b + 2] = false;
    t[a][b + 1] = false;
    t[a + 1][b] = false;
    t[a][b + 3] = false;
    t[a + 1][b + 4] = false;
    t[a + 3][b] = false;
    t[a + 4][b + 1] = false;
    t[a + 3][b + 4] = false;
    t[a + 4][b + 3] = false;
    int i = 0, j = 0;
    for (i = 2; i < n + 3 && t[i][2] == true; i++)
    {
        dp[i][2] = 1;
    }
    for (j = 3; j < m + 3 && t[2][j] == true; j++)
    {
        dp[2][j] = 1;
    }
    for (i = 3; i < n + 3; i++)
    {
        for (j = 3; j < m + 3; j++)
        {
            if (t[i][j] == false)
            {
                continue;
            }
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    cout << dp[n + 2][m + 2] << endl;
    return 0;
}