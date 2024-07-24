#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int t = 0, m = 0, n = 0;
    cin >> t;
    int i = 0, j = 0;
    for (i = 0; i < t; i++)
    {
        cin >> m >> n;
        vector<int> trap(n, 0);
        for (j = 0; j < n; j++)
        {
            cin >> trap[j];
        }
        vector<int> dp(n, 0);
        dp[0] = trap[0];
        dp[1] = trap[1];
        for (j = 2; j < n; j++)
        {
            dp[j] = min(dp[j - 1], dp[j - 2]) + trap[j];
        }
        int lf = 0;
        lf = m - dp[n - 1];
        if (lf > 0)
        {
            cout << lf << endl;
        }
        else
        {
            cout << "Can't get the top!" << endl;
        }
    }
    return 0;
}