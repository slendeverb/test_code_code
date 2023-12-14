#include <iostream>
using namespace std;

int n, k;
const int N = 1005;
long long a[N];
long long ans;

bool check(int idx, long long mid)
{
    long long cnt = 0;
    bool ok = 0;
    for (int i = idx; i <= n; i++)
    {
        if (a[i] >= mid)
        {
            ok = 1;
            break;
        }
        cnt += mid - a[i];
        mid--;
    }
    if (!ok)
    {
        return false;
    }
    if (cnt > k)
    {
        return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> k;
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            ans = max(ans, a[i]);
        }
        for (int i = 1; i < n; i++)
        {
            long long l = 0, r = 1e9, mid;
            while (l < r)
            {
                mid = (l + r + 1) >> 1;
                if (check(i, mid))
                {
                    l = mid;
                }
                else
                {
                    r = mid - 1;
                }
            }
            ans = max(ans, l);
        }
        cout << ans << "\n";
    }
    return 0;
}