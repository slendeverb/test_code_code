#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const int maxn = 1000005;
const long long INF = 100000000000000;

struct edge
{
    int v, next;
} e[maxn << 1];

int tot, head[maxn];

void Addedge(int u, int v)
{
    e[++tot].v = v;
    e[tot].next = head[u];
    head[u] = tot;
}

long long dp[maxn][3];
int father[maxn], a[maxn];

void dfs(int pos)
{
    dp[pos][0] = dp[pos][1] = dp[pos][2] = 0;
    dp[pos][1] = a[pos];
    dp[pos][2] = INF;
    for (int i = head[pos]; i; i = e[i].next)
    {
        int nxt = e[i].v;
        if (nxt == father[pos])
        {
            continue;
        }
        father[nxt] = pos;
        dfs(nxt);
        dp[pos][2] = min(dp[pos][2] + min(dp[nxt][1], dp[nxt][2]), dp[pos][0] + dp[nxt][1]); // dp[i][2]表示i这个点目前没有路由器安放，但是i在路由器的覆盖范围内（可以由它的一个儿子安放），i的子孙全部被路由器覆盖的最小代价
        dp[pos][1] = min(dp[pos][1] + min(dp[nxt][0], min(dp[nxt][1], dp[nxt][2])), INF);    // dp[i][1]表示i这个点安放了路由器，i的子孙全部被路由器覆盖的最小代价
        dp[pos][0] = min(dp[pos][0] + dp[nxt][2], INF);                                      // dp[i][0]表示i这个点目前没有路由器安放，i也不在路由器的覆盖范围内，i的子孙全部被路由器覆盖的最小代价
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        tot = 0;
        for (int i = 1; i <= n; i++)
            head[i] = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i < n; i++)
        {
            int u, v;
            cin >> u >> v;
            Addedge(u, v);
            Addedge(v, u);
        }
        dfs(1);
        long long ans = min(dp[1][1], dp[1][2]);
        cout << ans << "\n";
    }
    return 0;
}