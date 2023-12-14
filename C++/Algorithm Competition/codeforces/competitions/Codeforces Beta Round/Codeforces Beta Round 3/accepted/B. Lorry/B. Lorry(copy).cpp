#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 1e5 + 5;
int n, v;

set<pair<int, int>, greater<pair<int, int>>> s1, s2;

void solve()
{
    cin >> n >> v;
    int t, p;
    for (int i = 1; i <= n; i++)
    {
        cin >> t >> p;
        if (t == 1)
        {
            s1.emplace(p, i);
        }
        else
        {
            s2.emplace(p, i);
        }
    }

    // for (auto &x1 : s1)
    // {
    //     cout << x1.first << " " << x1.second << endl;
    // }
    // cout << ".......................\n";
    // for (auto &x2 : s2)
    // {
    //     cout << x2.first << " " << x2.second << endl;
    // }
    // cout << ".......................\n";

    int maxCarry = 0;
    vector<int> boatIdx;
    while (v >= 2 && s1.size() >= 2 && s2.size())
    {
        auto it1 = s1.begin();
        auto it2 = s2.begin();
        int p1 = it1->first;
        int p2 = next(it1)->first;
        int p3 = it2->first;
        if (p1 + p2 > p3)
        {
            maxCarry += p1;
            boatIdx.emplace_back(it1->second);
            s1.erase(it1);
            v -= 1;
        }
        else
        {
            maxCarry += p3;
            boatIdx.emplace_back(it2->second);
            s2.erase(it2);
            v -= 2;
        }
    }

    while (v >= 2 && s2.size())
    {
        auto it2 = s2.begin();
        maxCarry += it2->first;
        boatIdx.emplace_back(it2->second);
        s2.erase(it2);
        v -= 2;
    }
    while (v && s1.size())
    {
        auto it1 = s1.begin();
        maxCarry += it1->first;
        boatIdx.emplace_back(it1->second);
        s1.erase(it1);
        v -= 1;
    }

    cout << maxCarry << endl;
    for (int &x : boatIdx)
    {
        cout << x << " ";
    }
    cout << endl;
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("in.txt", "r", stdin), freopen("out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}