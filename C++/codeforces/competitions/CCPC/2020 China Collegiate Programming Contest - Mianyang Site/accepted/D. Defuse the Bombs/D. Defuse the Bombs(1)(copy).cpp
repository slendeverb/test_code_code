#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 3e5 + 7;
int a[MAXN], n;

bool check(ll x)
{
    ll sum = 0;
    x--; //因为我做的是到等于0 一开始先减减
    for (int i = 1; i <= n; i++)
    {
        if (a[i] < x)
            sum += x - a[i];
    }
    if (sum <= x)
        return true;
    else
        return false;
}

int main()
{
    int T, cas = 0;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        ll l = 0, r = 1e14, mid;
        ll ans;
        while (l <= r)
        {
            mid = (l + r) >> 1;
            if (check(mid))
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("Case #%d: %d\n", ++cas, ans);
    }
    return 0;
}
