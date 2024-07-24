#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

#define int long long
const int N = 3e4 + 10;
int n, cnt, a[N], b[N], c[N], Left[N], Right[N];

int lowbit(int x)
{
    return x & (-x);
}

void add(int x, int val)
{
    while (x <= N)
    {
        c[x] += val;
        x += lowbit(x);
    }
}

int query(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}

int Q(int val)
{
    return lower_bound(b + 1, b + 1 + cnt, val) - b;
}

signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    cnt = unique(b + 1, b + 1 + n) - (b + 1);
    for (int i = 1; i <= n; i++)
    {
        add(Q(a[i]), 1);
        Left[i] = query(Q(a[i]) - 1);
    }
    memset(c, 0, sizeof(c));
    for (int i = n; i >= 1; i--)
    {
        add(Q(a[i]), 1);
        Right[i] = n - i + 1 - query(Q(a[i]));
    }
    int ans = 0;
    for (int i = 2; i < n; i++)
    {
        ans += Left[i] * Right[i];
    }
    cout << ans << "\n";
    return 0;
}