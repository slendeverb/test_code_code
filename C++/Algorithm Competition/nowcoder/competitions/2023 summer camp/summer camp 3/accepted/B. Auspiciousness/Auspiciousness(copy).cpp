#include <iostream>
using namespace std;

// 考虑dp.设f(i,j,k)表示已经填了i个小数,j个大数,最后一段是小/大数的方案数,转移可以枚举下一段包含多少个数

// 将[1,n]的数看作0，将[n+1,2n]的数看作1，
// 则任何10，或者01都是合法的，只有00或者11有可能会不合法，
// 设[i][j][0/1]表示考虑了前i个，第i个为0/1时，共用了j个0的合法方案数，转移方程考虑枚举i往前是一连串的0或者1，枚举从哪里转移而来，
// 若由f[k][x][y]转移而来，那么在[k+1,i]这个区间全是0或者1，考虑合法方案这一段的填的数（从剩余的数中取这个区间长度的数出来）大小是固定的即从大到小或者从小到大放置，
// 考虑到i位置才不合法，则这一段数除了最小/最大的不能放在i（否则就合法），其它的都可以，
// 然后令剩下的数按照合法顺序放即可，最后i后面可以随便放，于是不合法方案就可以算出来了

int n, m, n2;
const int maxn = 310 << 1;
long long dp[maxn][maxn][2];
long long factorial[maxn], c[maxn][maxn];

void init()
{
    factorial[0] = 1;
    c[0][0] = 1;
    for (int i = 1; i <= n2; i++)
    {
        factorial[i] = factorial[i - 1] * i % m;
    }
    for (int i = 1; i <= n2; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % m;
        }
    }
    for (int i = 1; i <= n2; i++)
    {
        for (int j = 0; j <= n2; j++)
        {
            dp[i][j][0] = dp[i][j][1] = 0;
        }
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        n2 = n << 1;
        init();
        dp[0][0][0] = dp[0][0][1] = 1;
        long long ans = 0;
        for (int i = 1; i <= n2; i++)
        {
            for (int j = min(i, n); j >= 0; j--)
            {
                for (int k = i - 1; k >= 0; k--)
                {
                    int t0 = j - (i - k);
                    if (t0 < 0 || t0 > min(k, n))
                    {
                        continue;
                    }
                    dp[i][j][0] = (dp[i][j][0] + (dp[k][t0][1] * c[n - t0][i - k] % m)) % m;
                    ans = (ans + (dp[k][t0][1] * c[n - t0][i - k]) % m * (i - k - 1) % m * i % m * factorial[n2 - i] % m) % m;
                }
                for (int k = i - 1; k >= 0; k--)
                {
                    int t1 = (i - j) - (i - k);
                    if (t1 < 0 || t1 > min(k, n))
                    {
                        continue;
                    }
                    dp[i][j][1] = (dp[i][j][1] + (dp[k][j][0] * c[n - t1][i - k]) % m) % m;
                    ans = (ans + (dp[k][j][0] * c[n - t1][i - k]) % m * (i - k - 1) % m * i % m * factorial[n2 - i] % m) % m;
                }
            }
        }

        ans = (ans + (dp[n2][n][0] * n2) % m + (dp[n2][n][1] * n2) % m) % m;
        cout << ans << "\n";
    }
    return 0;
}