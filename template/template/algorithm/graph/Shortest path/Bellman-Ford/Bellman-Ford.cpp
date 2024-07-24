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

const int maxn = 1010;

struct edge
{
    int v, w;
};

vector<edge> e[maxn];
int dis[maxn];
const int inf = 0x3f3f3f3f;

bool bellmanford(int n, int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    bool flag; // 判断一轮循环过程中是否发生松弛操作
    for (int i = 1; i <= n; i++)
    {
        flag = false;
        for (int u = 1; u <= n; u++)
        {
            if (dis[u] == inf)
                continue;
            // 无穷大与常数加减仍然为无穷大
            // 因此最短路长度为 inf 的点引出的边不可能发生松弛操作
            for (auto ed : e[u])
            {
                int v = ed.v, w = ed.w;
                if (dis[v] > dis[u] + w)
                {
                    dis[v] = dis[u] + w;
                    flag = true;
                }
            }
        }
        // 没有可以松弛的边时就停止算法
        if (!flag)
            break;
    }
    // 第 n 轮循环仍然可以松弛时说明 s 点可以抵达一个负环
    return flag;
}