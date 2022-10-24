#include <iostream>
#include <cstring>
using namespace std;

typedef long long int ll;

ll dp[200000 + 10][2];
ll a[200000 + 10];
int main()
{

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        string s;
        cin >> s;
        s = " " + s;

        int pos = 0;

        for (int i = 1; i <= n; i++)
        {
            dp[i][0] = 0;
            dp[i][1] = 0;

            cin >> a[i];

            if (s[i] == '1')
                pos = i;
        }

        for (int i = pos; i >= 1; i--)
        {
            if (s[i] == '1')
            {

                if (s[i + 1] == '1')
                {

                    dp[i][1] = max(dp[i + 1][0], dp[i + 1][1]) + a[i];

                    dp[i][0] = max(dp[i + 1][1], dp[i + 1][0] + a[i]);
                }
                else
                {
                    dp[i][1] = max(dp[i + 1][0], dp[i + 1][1]) + a[i];

                    dp[i][0] = max(dp[i + 1][0], dp[i + 1][1]);
                }
            }
            else
            {
                if (s[i + 1] == '1')
                {
                    dp[i][1] = max(dp[i + 1][0], dp[i + 1][1]);

                    dp[i][0] = max(dp[i + 1][0] + a[i], dp[i + 1][1]);
                }
                else
                {
                    dp[i][1] = max(dp[i + 1][0], dp[i + 1][1]);

                    dp[i][0] = max(dp[i + 1][1], dp[i + 1][0]);
                }
            }
        }

        cout << max(dp[1][0], dp[1][1]) << endl;
    }

    return 0;
}