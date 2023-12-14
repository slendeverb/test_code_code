#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l = 0, r = n - 1;
    int ans = 0;
    while (s[l] == s[r] && l < r)
    {
        ans += 2;
        l++;
        r--;
    }

    stack<char> st;
    for (int i = l; i <= r; i++)
    {
        if (!st.empty())
        {
            if (st.top() == s[i])
            {
                st.pop();
                ans += 2;
            }
            else
            {
                st.emplace(s[i]);
            }
        }
        else
        {
            st.emplace(s[i]);
        }
    }
    cout << ans << "\n";
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}