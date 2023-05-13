#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calculateMaxScore(int n, int m, int x, vector<vector<char>> &matrix)
{
    vector<vector<int>> dp(n, vector<int>(m));

    // Initialize dp[0][0]
    dp[0][0] = (matrix[0][0] == '1') ? 1 : 0;

    for (int i = 1; i < n; i++)
    {
        dp[i][0] = dp[i - 1][0] + ((matrix[i][0] == '1') ? 1 : 0);
    }

    for (int j = 1; j < m; j++)
    {
        dp[0][j] = dp[0][j - 1] + ((matrix[0][j] == '1') ? 1 : 0);
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (matrix[i][j] == '1')
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
            }
            else if (matrix[i][j] == '?')
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
                x--;
                if (x < 0)
                {
                    dp[i][j]--;
                }
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n - 1][m - 1];
}

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int n, m, x;
        cin >> n >> m >> x;

        vector<vector<char>> matrix(n, vector<char>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> matrix[i][j];
            }
        }

        int maxScore = calculateMaxScore(n, m, x, matrix);
        cout << maxScore << endl;
    }

    return 0;
}
