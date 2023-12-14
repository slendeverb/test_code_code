#include <iostream>
using namespace std;

const int maxm = 110;
const int maxt = 1010;
struct Pick_herb
{
    int time;
    int value;
} p[maxm];

int dp[maxm][maxt];

int main()
{
    int t, m;
    while (cin >> t >> m)
    {
        for (int i = 1; i <= m; i++)
        {
            cin >> p[i].time >> p[i].value;
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 0; j <= t; j++)
            {
                if (p[i].time > j)
                {
                    dp[i][j] = dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - p[i].time] + p[i].value);
                }
            }
        }
        cout << dp[m][t] << "\n";
    }
    return 0;
}