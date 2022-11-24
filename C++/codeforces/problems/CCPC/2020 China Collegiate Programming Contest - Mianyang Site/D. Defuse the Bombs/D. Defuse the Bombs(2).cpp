#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve()
{
    static int count = 0;
    int n = 0;
    cin >> n;
    ll a[100001];
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    ll left = 0;
    ll right = (ll)1e14;
    ll ans = 0;
    while (left <= right)
    {
        ll mid = (left + right) / 2;
        ll tmp = 0;
        for (int i = 0; i < n; i++)
        {
            tmp += max((long long)0, mid - a[i] - 1); //统计总共需要的维持到0秒的秒数
        }
        if (tmp > mid - 1) //有一个炸弹到-1时全部爆炸，秒数可以到-1
        {
            right = mid - 1;
        }
        else
        {
            ans = mid;
            left = mid + 1;
        }
    }
    count++;
    printf("Case #%d: %ld\n", count, ans);
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}