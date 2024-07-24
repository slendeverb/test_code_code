#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int N = 2010;
const int M = 400;
int n, a[N], cnt1[N], cnt2[N];
long long sum[N], f[N];

bool is_perfect_square_number(int x)
{
    int y = sqrt(x);
    if (y * y == x)
    {
        return true;
    }
    return false;
}

void solve(int l, int r, int x)
{
    int pos = sum[r] - sum[l - 1];
    for (int k = -300; k <= 300; k++)
    {
        if (is_perfect_square_number(pos + k))
        {
            f[M + k] += x;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        memset(cnt1, 0, sizeof(cnt1));
        memset(cnt2, 0, sizeof(cnt2));
        memset(sum, 0, sizeof(sum));
        memset(f, 0, sizeof(f));
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            sum[i] = sum[i - 1] + a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= i - 1; j++)
            {
                if (is_perfect_square_number(sum[i] - sum[j]))
                {
                    cnt1[i]++;
                }
            }
            cnt1[i] += cnt1[i - 1];
        }
        for (int i = n; i >= 1; i--)
        {
            for (int j = i; j <= n; j++)
            {
                if (is_perfect_square_number(sum[j] - sum[i - 1]))
                {
                    cnt2[i]++;
                }
            }
            cnt2[i] += cnt2[i + 1];
        }

        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = i; j <= n; j++)
            {
                solve(i, j, 1);
            }
            for (int j = 1; j <= i - 1; j++)
            {
                solve(j, i - 1, -1);
            }
            long long t = 0;
            for (int j = 1; j <= 300; j++)
            {
                t = max(t, f[j - a[i] + M]);
            }
            ans = max(ans, cnt1[i - 1] + cnt2[i + 1] + t);
        }
        cout << ans << "\n";
    }
    cout.flush();
    return 0;
}