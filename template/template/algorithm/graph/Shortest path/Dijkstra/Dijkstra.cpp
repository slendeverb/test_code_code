// 类似BFS
// 当点u距离不是最短时，用点u更新的点v也一定不是最短距离
// 找到距离确定的点，更新相邻的点，之后不再考虑这个点
// Dijkstra算法只能求解非负权图的最短路
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int maxn = 1010;

struct edge
{
    int v, w;
};

struct node
{
    int dis, u;
    bool operator>(const node &a) const { return dis > a.dis; }
};

vector<edge> e[maxn];
int dis[maxn], vis[maxn];
priority_queue<node, vector<node>, greater<node>> q;

void dijkstra(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    for (int i = 1; i <= n; i++)
    {
        int u = 0, mindis = 0x3f3f3f3f;
        for (int j = 1; j <= n; j++)
            if (!vis[j] && dis[j] < mindis)
                u = j, mindis = dis[j];
        vis[u] = true;
        for (auto ed : e[u])
        {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w)
                dis[v] = dis[u] + w;
        }
    }
}

void dijkstra(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        int u = q.top().u;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto ed : e[u])
        {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}
