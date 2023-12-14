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
using namespace std;

#define int long long

// 首先考虑拆绝对值号，不妨令$a_{i}<b_{i}$(读入时进行预处理)，在权值和最大的前提下，显然会有$n$个$a_{i}$产生负贡献，$n$个$b_{i}$产生正贡献。
// 那么如何确定每个数对提供正贡献还是负贡献？
// 由于$a_{i}<b_{i}$一定成立，我们任取两对进行分析。要使得$b_{2}-a_{1}>b_{1}-a_{2}$，显然需要$a_{1}+b_{1}<a_{2}+b_{2}$。
// 那么我们只需要根据$a_{i}+b_{i}$的大小进行排序，然后取前$n$个$a_{i}$作为负贡献，取后$n$个$b_{i}$作为正贡献即可

const int N = 1e5 + 5;
int n;

struct node
{
    int a, b;
    bool operator<(const node &x) const
    {
        return a + b < x.a + x.b;
    }
} p[N << 1];

void solve()
{
    cin >> n;
    int total = n << 1;
    for (int i = 1; i <= total; i++)
    {
        cin >> p[i].a >> p[i].b;
        if (p[i].a > p[i].b)
        {
            swap(p[i].a, p[i].b);
        }
    }
    sort(p + 1, p + 1 + total);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans -= p[i].a;
    }
    for (int i = n + 1; i <= total; i++)
    {
        ans += p[i].b;
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}