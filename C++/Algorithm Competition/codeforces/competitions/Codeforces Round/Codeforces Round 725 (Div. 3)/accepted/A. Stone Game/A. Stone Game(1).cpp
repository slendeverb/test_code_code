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
        for (int i = 0; i < n; i++)
        {
            int x = 0;
            cin >> x;
            ma = ma > x ? ma : x;
            mi = mi < x ? mi : x;
            mp[x] = i;
        }
        int ans = 0;
        if (mp[mi] < mp[ma])
        {
            ans = min(mp[mi] - 0 + 1 + n - 1 - mp[ma] + 1, min(n - 1 - mp[mi] + 1, mp[ma] - 0 + 1));
        }
        else
        {
            ans = min(mp[mi] - 0 + 1 + n - 1 - mp[ma] + 1, min(n - 1 - mp[ma] + 1, mp[mi] - 0 + 1));
        }
        cout << ans << "\n";
    }
    return 0;
}