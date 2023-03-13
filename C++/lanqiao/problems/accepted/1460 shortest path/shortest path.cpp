#include <iostream>
#include <algorithm>
using namespace std;

int dp[2022];

int main()
{
    for (int i = 1; i <= 2021; i++)
    {
        for (int j = i + 1; j <= i + 21; j++)
        {
            if (j > 2021)
            {
                break;
            }
            if (dp[j] == 0)
            {
                dp[j] = dp[i] + i * j / __gcd(i, j);
            }
            else
            {
                dp[j] = min(dp[j], dp[i] + i * j / __gcd(i, j));
            }
        }
    }
    cout << dp[2021] << "\n";
    return 0;
}