#include <iostream>
using namespace std;

const int maxn = 1e6 + 10;

int a[maxn];
int b[maxn];
long long dp[maxn][3];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int maxx_cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (x == 1)
        {
            b[++maxx_cnt] = i;
        }
    }
    a[0] = -1e18, a[n + 1] = -1e18;
    dp[1][0] = a[b[1] - 1];
    dp[1][1] = a[b[1]];
    dp[1][2] = a[b[1] + 1];
    for (int i = 2; i <= maxx_cnt; i++)
    {
        int prev = b[i - 1], pos = b[i];
        if (pos - prev == 1)
        {
            dp[i][0] = dp[i - 1][0] + a[pos - 1];                                       // dp[i][0]表示盖子放在左边
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + a[pos];                        // dp[i][1]表示盖子放在中间
            dp[i][2] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]) + a[pos + 1]; // dp[i][2]表示盖子放在右边
        }
        else if (pos - prev == 2)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]) + a[pos - 1]; // 由于pos-prev==2,则如果dp[i-1]选择放在右边的话，就会覆盖到dp[i]放左边,所以不包含dp[i-1][2]
            dp[i][1] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]) + a[pos];
            dp[i][2] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]) + a[pos + 1];
        }
        else
        {
            dp[i][0] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]) + a[pos - 1];
            dp[i][1] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]) + a[pos];
            dp[i][2] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]) + a[pos + 1];
        }

        long long ans = max(max(dp[maxx_cnt][0], dp[maxx_cnt][1]), dp[maxx_cnt][2]);
        cout << ans << "\n";
    }
    return 0;
}