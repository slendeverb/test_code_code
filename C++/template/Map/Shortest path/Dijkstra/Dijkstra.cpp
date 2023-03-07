// 类似BFS
// 当点u距离不是最短时，用点u更新的点v也一定不是最短距离
// 找到距离确定的点，更新相邻的点，之后不再考虑这个点
// Dijkstra算法只能求解非负权图的最短路
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1010;

struct Edge
{
    int v, w;
};

struct Node
{
    int v, dis;
    bool operator<(const Node &node) const
    {
        return dis > node.dis;
    }
};

vector<Edge> adj[N];
int dis[N];
bool vis[N];

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    priority_queue<Node> q;
    q.push({s, 0});
    dis[s] = 0;
    while (!q.empty())
    {
        int u = q.top().v;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto it : adj[u])
        {
            if (dis[it.v] > dis[u] + it.w)
            {
                dis[it.v] = dis[u] + it.w;
                q.push({it.v, dis[it.v]});
            }
        }
    }
}