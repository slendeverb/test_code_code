// 最短路不存在：（1）不存在路径（2）能到达负环
// 任意一条最短路，经过边数不会超过n-1条，经过点数不会超过n个
// dis[u]表示s到u的距离，初始时dis[s]=0,其余dis[u]=INF
// 选不选通过这条边可以得到
// dis[v]=min(dis[v],dis[u]+w[u][v])
// 用上式进行n-1轮更新即可
// 如果n轮时仍有能更新，则说明到达负环
// 若图不连通，判负环记得建立超级源点
#include <cstring>
#include <vector>
using namespace std;

const int N = 1010;
int n, fr;

struct Edge
{
    int v, w;
};
vector<Edge> adj[N];
int dis[N];
bool Bellman_Ford(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    for (int i = 1; i <= n; ++i)
    {
        bool flag = 0;
        for (int u = 1; u <= n; ++u)
        {
            for (auto it : adj[u])
            {
                if (dis[it.v] > dis[fr] + it.w)
                {
                    dis[it.v] = dis[fr] + it.w;
                    flag = 1;
                }
            }
        }
        if (!flag)
            return true;
    }
    return false;
}
