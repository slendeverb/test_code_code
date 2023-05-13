#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 510;
const int maxx = 1010;
char a[maxn][maxn];
int dp[maxn][maxn];

int main()
{
	ios::sync_with_stdio(false), cin.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n, m, x;
		cin >> n >> m >> x;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				cin >> a[i][j];
			}
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (a[i][j] == '0')
				{
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
				if (a[i][j] == '1')
				{
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
				}
				if (a[i][j] == '?')
				{
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
					x--;
					if (x < 0)
					{
						dp[i][j]--;
					}
				}
			}
		}
		cout << dp[n][m] << "\n";
	}
	return 0;
}