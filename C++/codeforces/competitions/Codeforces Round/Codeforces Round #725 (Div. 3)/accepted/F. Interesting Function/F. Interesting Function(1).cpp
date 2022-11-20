#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve()
{
    int l, r;
    cin >> l >> r;
    int num = r - l;
    int tmp = l;
    int ans = 0;
    while (num--)
    {
        l++;
        int ret = l;
        while (tmp)
        {
            if ((tmp % 10) != (ret % 10))
            {
                ans++;
            }
            tmp /= 10;
            ret /= 10;
        }
        if (ret > 0)
        {
            ans++;
        }
        tmp = l;
    }
    cout << ans << endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}