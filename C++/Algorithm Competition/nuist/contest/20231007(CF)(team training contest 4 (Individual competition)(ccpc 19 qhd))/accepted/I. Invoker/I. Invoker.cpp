#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int dp[N][10];

char skill[10][6][4] = {{"QQQ", "QQQ", "QQQ", "QQQ", "QQQ", "QQQ"},
                        {"QQW", "QWQ", "WQQ", "WQQ", "WQQ", "WQQ"},
                        {"QQE", "QEQ", "EQQ", "EQQ", "EQQ", "EQQ"},
                        {"WWW", "WWW", "WWW", "WWW", "WWW", "WWW"},
                        {"QWW", "WQW", "WWQ", "WWQ", "WWQ", "WWQ"},
                        {"WWE", "WEW", "EWW", "EWW", "EWW", "EWW"},
                        {"EEE", "EEE", "EEE", "EEE", "EEE", "EEE"},
                        {"QEE", "EQE", "EEQ", "EEQ", "EEQ", "EEQ"},
                        {"WEE", "EWE", "EEW", "EEW", "EEW", "EEW"},
                        {"QWE", "QEW", "EQW", "EWQ", "WEQ", "WQE"}};

int dis(char a[], char b[])
{
    if (a[0] == b[0] && a[1] == b[1] && a[2] == b[2])
    {
        return 0;
    }
    else if (a[1] == b[0] && a[2] == b[1])
    {
        return 1;
    }
    else if (a[2] == b[0])
    {
        return 2;
    }
    return 3;
}

void solve()
{
    string s;
    unordered_map<char, int> mp;
    mp['Y'] = 0, mp['V'] = 1, mp['G'] = 2,
    mp['C'] = 3, mp['X'] = 4, mp['Z'] = 5,
    mp['T'] = 6, mp['F'] = 7, mp['D'] = 8, mp['B'] = 9;
    while (cin >> s)
    {
        int n = s.size();
        memset(dp, 0x3f3f3f3f, sizeof(dp));
        for (int i = 0; i < 6; i++)
        {
            dp[0][i] = 3;
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 6; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + dis(skill[mp[s[i]]][j], skill[mp[s[i - 1]]][k]));
                }
            }
        }
        int ans = 0x3f3f3f3f;
        for (int i = 0; i < 6; i++)
        {
            ans = min(ans, dp[n - 1][i]);
        }
        cout << ans + n << "\n";
    }
}

int main()
{
    // ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}