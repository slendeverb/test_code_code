#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 3010;
const int mod = 1e9 + 7;

int a[maxn], b[maxn];
long long dp[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            b[i] = a[i];
        }
        sort(b + 1, b + 1 + n);
        int m = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i == 1 || b[i] > b[i - 1])
            {
                b[++m] = b[i];
            }
        }
        for (int i = 1; i <= n; i++)
        {
            a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
        }
        sort(a + 1, a + 1 + n);
        for (int i = 1; i <= m; i++)
        {
            dp[i] = 1;
        }
        cout << m << "\n";
        long long sum, ans;
        for (int i = 2; i <= n; i++)
        {
            sum = 0, ans = 0;
            for (int j = a[i - 1]; j < a[i]; j++)
            {
                sum = (sum + dp[j]) % mod;
            }
            for (int j = a[i]; j <= m; j++)
            {
                sum = (sum + dp[j]) % mod;
                dp[j] = sum;
                ans = (ans + sum) % mod;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}