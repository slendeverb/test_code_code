// 队列优化的Bellman-Ford算法
// 减少无用的更新
// 被更新的点扔进队列
// 当最短路通过n+1个点时，到达负环
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1010;
int n, s;

struct Edge
{
    int v, w;
};

vector<Edge> adj[N];
int dis[N], cnt[N];
bool vis[N];

int spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    vis[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto it : adj[u])
        {
            if (dis[it.v] > dis[u] + it.w)
            {
                dis[it.v] = dis[u] + it.w;
                cnt[it.v] = cnt[u] + 1;
                if (cnt[it.v] >= n)
                    return false;
                if (vis[it.v] == 0)
                {
                    q.push(it.v);
                    vis[it.v] = 1;
                }
            }
        }
    }
    return true;
}
