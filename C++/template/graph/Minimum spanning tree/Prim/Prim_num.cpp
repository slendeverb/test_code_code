// 类似Dijkstra算法
// 找到离当前生成树最近的点，加入生成树
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1010;
int n, m;

int adj[N][N];
bool vis[N];
int dis[N];

int Prim()
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        int u = -1;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && (u == -1 || dis[j] < dis[u]))
                u = j;
        res += dis[u];
        vis[u] = 1;
        for (int j = 1; j <= n; ++j)
            if (!vis[j])
                dis[j] = min(dis[j], adj[u][j]);
    }
    return res;
}