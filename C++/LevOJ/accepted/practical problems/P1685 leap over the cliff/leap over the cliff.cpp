#include <iostream>
using namespace std;

long long dp[50];

int main()
{
    int n;
    dp[1] = 3, dp[2] = 9;
    for (int i = 3; i <= 40; i++)
    {
        dp[i] = 3 * dp[i - 2] + 2 * (dp[i - 1] - dp[i - 2]);
    }
    while (cin >> n)
    {
        cout << dp[n] << "\n";
    }
    return 0;
}