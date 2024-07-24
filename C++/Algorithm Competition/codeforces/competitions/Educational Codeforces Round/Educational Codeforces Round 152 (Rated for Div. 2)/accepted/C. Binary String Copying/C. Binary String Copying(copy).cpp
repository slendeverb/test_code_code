#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        vector<int> prev_zero(n + 1, 0), next_one(n + 2, n + 1);
        for (int i = 1; i <= n; i++)
        {
            if (s[i - 1] == '0')
            {
                prev_zero[i] = i;
            }
            else
            {
                prev_zero[i] = prev_zero[i - 1];
            }
        }
        for (int i = n; i >= 1; i--)
        {
            if (s[i - 1] == '1')
            {
                next_one[i] = i;
            }
            else
            {
                next_one[i] = next_one[i + 1];
            }
        }
        set<pair<int, int>> se;
        long long ans = 0;
        for (int i = 1; i <= m; i++)
        {
            int l, r;
            cin >> l >> r;
            l = next_one[l];
            r = prev_zero[r];
            if (l < r)
            {
                se.insert({l, r});
            }
            else
            {
                ans = 1;
            }
        }
        ans += se.size();
        cout << ans << "\n";
    }
    return 0;
}