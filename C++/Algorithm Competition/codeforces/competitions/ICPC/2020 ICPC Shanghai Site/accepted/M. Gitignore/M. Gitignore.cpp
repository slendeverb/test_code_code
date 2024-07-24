#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
int n, m, id, ans;
string s, sub, sub_prev;
int fa[N], vis[N];
map<string, int> mp;
set<int> strIgnore, strNotIgnore;

void init()
{
    id = 0, ans = 0;
    mp.clear();
    strIgnore.clear();
    strNotIgnore.clear();
    memset(fa, 0, sizeof(fa));
    memset(vis, 0, sizeof(vis));
    mp["0"] = 0;
    vis[0] = 1;
}

void scanAndInit()
{
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        sub = "0";
        sub_prev = sub;
        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] == '/')
            {
                sub_prev = sub;
                sub = s.substr(0, j);
                if (!mp.count(sub))
                {
                    mp[sub] = ++id;
                }
                fa[mp[sub]] = mp[sub_prev];
            }
        }
        sub_prev = sub;
        sub = s;
        if (!mp.count(sub))
        {
            mp[sub] = ++id;
        }
        strIgnore.emplace(mp[sub]);
        fa[mp[sub]] = mp[sub_prev];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> s;
        sub = "0";
        sub_prev = sub;
        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] == '/')
            {
                sub_prev = sub;
                sub = s.substr(0, j);
                if (!mp.count(sub))
                {
                    mp[sub] = ++id;
                }
                fa[mp[sub]] = mp[sub_prev];
            }
        }
        sub_prev = sub;
        sub = s;
        if (!mp.count(sub))
        {
            mp[sub] = ++id;
        }
        strNotIgnore.emplace(mp[sub]);
        fa[mp[sub]] = mp[sub_prev];
    }
}

void setNotIgnore()
{
    for (auto it : strNotIgnore)
    {
        auto tmp = it;
        while (tmp != 0)
        {
            vis[tmp] = 1;
            tmp = fa[tmp];
        }
    }
}

void countMinIgnore()
{
    for (auto it : strIgnore)
    {
        auto tmp = it;
        while (true)
        {
            if (vis[fa[tmp]] == 0)
            {
                tmp = fa[tmp];
            }
            else if (vis[fa[tmp]] == 1)
            {
                vis[tmp] = 2;
                break;
            }
            else if (vis[fa[tmp]] == 2)
            {
                break;
            }
        }
    }
    for (int i = 1; i <= id; i++)
    {
        if (vis[i] == 2)
        {
            ans++;
        }
    }
    cout << ans << "\n";
}

void solve()
{
    cin >> n >> m;
    init();
    scanAndInit();
    setNotIgnore();
    countMinIgnore();
}

int main()
{
    // ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}