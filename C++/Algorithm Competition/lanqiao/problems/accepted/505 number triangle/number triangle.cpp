#include <iostream>
using namespace std;

int a[210][210], dp[210][210];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cin >> a[i][j];
        }
    }
    dp[1][1] = a[1][1];
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            dp[i][j] = a[i][j] + max(dp[i - 1][j], dp[i - 1][j - 1]);
        }
    }
    cout << max(dp[n][(n + 1) / 2], dp[n][(n + 2) / 2]); // 因为左右不能超过一步，因此答案在中间两个
    return 0;
}