#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

const int MAXN = 305;
int a[MAXN];
long long sum[MAXN];

set<int> square;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    for (int i = 1; i * i <= 1e5; i++)
    {
        square.insert(i * i);
    }
    while (T--)
    {
        int n;
        cin >> n;
        long long ans = 0;
        int minn = 400;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            int tmp = a[i];
            for (int j = 1; j <= 300; j++)
            {
                a[i] = j;
                sum[0] = 0;
                sum[1] = a[1];
                for (int k = 2; k <= n; k++)
                {
                    sum[k] = sum[k - 1] + a[k];
                }
                long long cnt = 0;
                for (int p = 1; p <= n; p++)
                {
                    for (int q = p; q <= n; q++)
                    {
                        long long tmp = sum[q] - sum[p - 1];
                        if (square.count(tmp))
                        {
                            cnt++;
                        }
                    }
                }
                ans = max(ans, cnt);
            }
            a[i] = tmp;
        }
        std::cout << ans << "\n";
    }
    cout.flush();
    return 0;
}