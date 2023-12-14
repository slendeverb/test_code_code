#include <iostream>
using namespace std;

// 考虑从左到右扫，只要当前和为偶数就把它切开
// 那么我们可以得到这个区间最多能分成多少个偶数部分
// 这个过程可以通过记录前缀和奇偶性的前缀和来维护

const int MAXN = 1e5 + 5;
int a[MAXN], sum[MAXN], sum2[MAXN];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int n, q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            sum[i] = (sum[i - 1] + a[i]) % 2;
        }
        for (int i = 1; i <= n; i++)
        {
            sum2[i] = sum2[i - 1] + (sum[i] ^ 1) % 2;
        }
        while (q--)
        {
            int x, y, k, t;
            cin >> x >> y >> k;
            if (sum[x - 1] == 0)
            {
                t = sum2[y] - sum2[x - 1];
            }
            else
            {
                t = (y - x + 1) - (sum2[y] - sum2[x - 1]);
            }
            if (t >= k && (sum[y] - sum[x - 1]) % 2 == 0)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
    cout.flush();
    return 0;
}