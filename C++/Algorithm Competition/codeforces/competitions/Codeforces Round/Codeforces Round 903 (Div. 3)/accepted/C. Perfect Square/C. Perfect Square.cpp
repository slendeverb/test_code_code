// #include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <cstring>
#include <algorithm>
using namespace std;

#define int long long

int n;
string s;
vector<string> square;

string maxStr(const string &a, const string &b)
{
    string res = "";
    for (int i = 0; i < a.size(); i++)
    {
        res += max(a[i], b[i]);
    }
    return res;
}

int dis(const string &maxx, const vector<string> &line)
{
    int res = 0;
    for (int i = 0; i < line.size(); i++)
    {
        for (int j = 0; j < line[i].size() - 1; j++)
        {
            res += maxx[j] - line[i][j];
        }
    }
    return res;
}

void solve()
{
    cin >> n;
    square.clear();
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        square.emplace_back(s);
    }
    int sum = 0;
    for (int i = 0; i < (n >> 1); i++)
    {
        vector<string> line(4);
        for (int j = i; j < n - i; j++)
        {
            line[0] += square[i][j];
            line[1] += square[j][n - 1 - i];
            line[2] += square[n - 1 - i][n - 1 - j];
            line[3] += square[n - 1 - j][i];
        }
        string maxx = maxStr(line[0], maxStr(line[1], maxStr(line[2], line[3])));
        sum += dis(maxx, line);
    }
    cout << sum << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}