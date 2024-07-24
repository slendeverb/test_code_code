#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <iterator>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <map>
#include <stack>
#include <set>
#include <queue>
#include <iomanip>
#include <bitset>
#include <unordered_map>
using namespace std;

stringstream ss;
#define endl "\n"
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<pair<int, int>, int> PIII;
const int N = 3e5 + 10, M = 20, mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, q;
int p[2 * N]; // 扩展一倍并查集规模

int find(int x)
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

void merge(int x, int y)
{
    int px = find(x);
    int py = find(y);
    if (px != py)
        p[px] = py;
}

void solve()
{
    cin >> n;
    map<int, int> mp; // 记数字次数
    for (int i = 1; i <= 2 * n; i++)
        p[i] = i;
    int f = 1;
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        mp[a]++, mp[b]++;
        if (mp[a] > 2 || mp[b] > 2)
            f = 0;
        if (a == b)
            f = 0;
        int x = a, y = b, dx = a + n, dy = b + n; // x,y在一个集合, dx,dy在另一个集合
        if (find(x) == find(y))
            f = 0;
        else
        {
            merge(x, dy);
            merge(y, dx);
        }
    }

    if (f)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    //    solve();
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
}