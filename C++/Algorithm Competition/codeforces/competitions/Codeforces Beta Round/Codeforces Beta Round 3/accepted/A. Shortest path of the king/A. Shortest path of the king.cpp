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
#define endl "\n"

struct Cor
{
    char row;
    int col;
    void input()
    {
        cin >> row >> col;
    }
};

void solve()
{
    Cor src, dst;
    src.input(), dst.input();
    int dx = dst.row - src.row;
    int dy = dst.col - src.col;
    vector<string> ans;
    while (dx || dy)
    {
        if (dx && dy)
        {
            if (dx < 0 && dy < 0)
            {
                ans.emplace_back("LD");
                dx++, dy++;
            }
            else if (dx < 0 && dy > 0)
            {
                ans.emplace_back("LU");
                dx++, dy--;
            }
            else if (dx > 0 && dy < 0)
            {
                ans.emplace_back("RD");
                dx--, dy++;
            }
            else
            {
                ans.emplace_back("RU");
                dx--, dy--;
            }
        }
        else
        {
            if (dx)
            {
                if (dx > 0)
                {
                    ans.emplace_back("R");
                    dx--;
                }
                else
                {
                    ans.emplace_back("L");
                    dx++;
                }
            }
            else
            {
                if (dy > 0)
                {
                    ans.emplace_back("U");
                    dy--;
                }
                else
                {
                    ans.emplace_back("D");
                    dy++;
                }
            }
        }
    }
    cout << ans.size() << endl;
    for (auto elem : ans)
    {
        cout << elem << endl;
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}