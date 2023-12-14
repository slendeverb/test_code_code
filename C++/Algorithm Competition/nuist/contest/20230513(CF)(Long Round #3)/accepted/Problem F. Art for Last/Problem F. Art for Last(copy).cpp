// 将 A 排序后，枚举所选区间的端点，单调队列维护区间中差分项的最小值即可得到 min 项，区间左右端点值之差即为 max项，取 min · max 最小的区间即可

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 500010;
int a[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);

    multiset<int> b;
    for (int i = 2; i <= k - 1; i++)
        b.insert(a[i] - a[i - 1]);

    LL res = 1e18;
    for (int i = k; i <= n; i++)
    {
        b.insert(a[i] - a[i - 1]);
        res = min(res, (LL)*b.begin() * (a[i] - a[i - k + 1]));
        b.erase(b.lower_bound(a[i - k + 2] - a[i - k + 1]));
    }
    cout << res;

    return 0;
}
