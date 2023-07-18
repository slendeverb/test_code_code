#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;
int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        mp.clear();
        int n = 0;
        cin >> n;
        int ma = 0;
        int mi = INT_MAX;
        for (int i = 1; i <= n; i++)
        {
            int x = 0;
            cin >> x;
            ma = ma > x ? ma : x;
            mi = mi < x ? mi : x;
            mp[x] = i;
        }
        int ans = 0;
        ans = min(min(max(mp[mi], mp[ma]), max(n - mp[mi] + 1, n - mp[ma] + 1)), min(mp[mi] + n - mp[ma] + 1, mp[ma] + n - mp[mi] + 1));
        if (n == 2)
        {
            ans = 2;
        }
        cout << ans << "\n";
    }
    return 0;
}