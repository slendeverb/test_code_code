//思路：
///因为给出的c是单调递增的，且一个城市必须要在被征服后才能搬迁过去，
//那我们就需要贪心决定搬迁的位置使征服所有城市的花费最少,
//可以进行前缀和处理计算出当前城市到之后所有城市所有距离之和，
//再通过比较当前城市是否搬迁的花费，如果搬过去和征服的消耗小于不搬的，那就搬过去。

#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll c[200005];
ll s[200005];
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, a, b;
        cin >> n >> a >> b;
        for (int i = 1; i <= n; i++)
        {
            cin >> c[i];
        }
        for (int i = n; i >= 1; i--)
        {
            s[i] = s[i + 1] + c[i];
        }
        ll ans = 0;
        ll pos = 0;
        for (int i = 1; i <= n; i++)
        {
            ans += (c[i] - pos) * b;
            if ((s[i + 1] - (n - i) * pos) * b >= b * (s[i + 1] - (n - i) * c[i]) + a * (c[i] - pos))
            {
                ans += a * (c[i] - pos);
                pos = c[i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}