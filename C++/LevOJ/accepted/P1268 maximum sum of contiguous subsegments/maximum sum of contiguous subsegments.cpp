#include <iostream>
using namespace std;

const int maxn = 1e4 + 10;
long long dp[maxn];

int main()
{
    int n;
    while (cin >> n)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> dp[i];
        }
        long long maxx = dp[1];
        for (int i = 2; i <= n; i++)
        {
            if (dp[i - 1] + dp[i] >= dp[i])
            {
                dp[i] = dp[i - 1] + dp[i];
            }
            maxx = max(dp[i], maxx);
        }
        cout << maxx << "\n";
    }
    return 0;
}