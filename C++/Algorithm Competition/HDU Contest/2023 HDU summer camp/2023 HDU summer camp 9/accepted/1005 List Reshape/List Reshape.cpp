#include <bits/stdc++.h>
using namespace std;

string s;
int x, y;

void solve()
{
    cin.get();
    getline(cin, s);
    cin >> x >> y;
    string ans;
    ans.push_back('[');
    size_t pos = 1;
    for (int i = 1; i <= x; i++)
    {
        ans.push_back('[');
        int cnt = 0;
        string temp;
        while (pos < s.size())
        {
            char ch = s[pos];
            if (isdigit(ch))
            {
                temp.push_back(ch);
                pos++;
            }
            else if (ch == ',' || ch == ']')
            {
                ans += temp;
                temp.clear();
                cnt++;
                if (cnt == y)
                {
                    break;
                }
                if (pos < s.size() - 1 && ch == ',')
                {
                    ans.push_back(s[pos]);
                    pos++;
                }
            }
            else
            {
                ans.push_back(ch);
                pos++;
            }
        }
        ans.push_back(']');
        while (!isdigit(s[pos]) && pos < s.size() - 1)
        {
            ans.push_back(s[pos]);
            pos++;
        }
    }
    ans.push_back(']');
    cout << ans << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    return 0;
}