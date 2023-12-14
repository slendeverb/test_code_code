#include <bits/stdc++.h>
using namespace std;

#define int long long

int t, n, m;

const int N = 3e5 + 10;
int root[N]; //记录根节点
int road[N]; //记录同一集合通路
int cnt[N];  //记录同一集合人数

void initset()
{
    for (int i = 0; i <= n; i++)
    {
        root[i] = i;
        road[i] = 0;
        cnt[i] = 1;
    }
}

int find(int x)
{
    return x == root[x] ? x : root[x] = find(root[x]); //路径压缩
}

void merge(int x, int y)
{
    int dx = find(x);
    int dy = find(y);
    if (dx != dy) //不同根
    {
        cnt[dx] += cnt[dy];   //集合人数叠加
        road[dx] += road[dy]; //集合通路数叠加

        root[dy] = dx; //并根在增加操作之后
        road[dx]++;    //并根时增加的一条通路
    }
    else
    {
        road[dx]++; //同根，只有通路数增加
    }
}

void solve()
{
    static int count = 0;
    int ans = 0;
    cin >> n >> m;
    initset();
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        merge(x, y);
    }
    for (int i = 1; i <= n; i++)
    {
        if (root[i] == i)
        {
            int tmp = road[i] - cnt[i];
            if (tmp >= 0)
            {
                ans += tmp;
            }
        }
    }
    printf("Case #%d: %d\n", ++count, ans);
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}