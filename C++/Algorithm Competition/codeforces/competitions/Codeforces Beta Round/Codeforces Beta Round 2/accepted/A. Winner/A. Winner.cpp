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
#include <cmath>
#include <algorithm>
#include <utility>
using namespace std;

#define int long long

struct node
{
    node(string s, int score) : s(s), score(score) {}
    string s;
    int score;
    bool operator<(const node &x) const
    {
        return score < x.score;
    }
};

priority_queue<node, vector<node>, less<node>> pq;
unordered_map<string, vector<pair<int, int>>> mp;
int n;
string s;
int x;

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        cin >> x;
        if (!mp.count(s))
        {
            mp[s].emplace_back(x, i);
        }
        else
        {
            mp[s].emplace_back(mp[s].back().first + x, i);
        }
    }
    for (auto elem : mp)
    {
        pq.emplace(elem.first, elem.second.back().first);
    }
    int m = pq.top().score;
    string ans = "";
    int minGameNum = 1e9;
    while (!pq.empty())
    {
        if (pq.top().score != m)
        {
            break;
        }
        auto tmp = pq.top();
        pq.pop();
        int sz = mp[tmp.s].size();
        for (int i = 0; i < sz; i++)
        {
            if (mp[tmp.s][i].first >= m && mp[tmp.s][i].second < minGameNum)
            {
                ans = tmp.s;
                minGameNum = mp[tmp.s][i].second;
                break;
            }
        }
    }
    cout << ans << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    // cout.flush();
    return 0;
}