#include <iostream>
#include <cmath>
using namespace std;
#define int long long

const int N = 1e6 + 10;
int n;
int dis[N], t[N];
long long ans;

signed main()
{
    cin >> n;
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> dis[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i];
    }
    if (n % 2 == 1)
    {
        int t1 = 0;
        int t2 = 0;
        for (int i = 1; i <= n / 2; i++)
        {
            t1 += t[i];
            t1 += dis[i];
            t2 += t[n - i + 1];
            t2 += dis[n - i];
        }
        int tmp = abs(t1 - t2);
        if (t[(1 + n) / 2] - tmp > 0)
        {
            ans = t[(1 + n) / 2] - tmp;
        }
    }
    else
    {
        int t1 = 0;
        int t2 = 0;
        int t3 = 0;
        int t4 = 0;
        for (int i = 1; i <= n / 2 - 1; i++)
        {
            t1 += t[i];
            t1 += dis[i];
            t4 += t[n - i + 1];
            t4 += dis[n - i];
        }
        for (int i = 1; i <= n / 2; i++)
        {
            t2 += t[i];
            t2 += dis[i];
            t3 += t[n - i + 1];
            t3 += dis[n - i];
        }
        int tmp1 = abs(t1 - t3);
        int tmp2 = abs(t2 - t4);
        if (t[n / 2] - tmp1 > 0)
        {
            ans += t[n / 2] - tmp1;
        }
        if (t[n / 2 + 1] - tmp2 > 0)
        {
            ans += t[n / 2 + 1] - tmp2;
        }
    }
    cout << ans << "\n";
    return 0;
}