// dis[0][u][v]表示只允许通过一条边，u,v之间的距离
// dis[i][u][v]表示允许通过点1到i中转，u,v之间的距离

// u到v的路径可以选择去或不去k中转，所以u到v的最短路为
// dis[i][u][v]=min(dis[i-1][u][v],dis[i-1][u][k]+dis[i-1][k][v])
// 因为第一维对答案没有影响，所以可以忽略，即
// dis[u][v]=min(dis[u][i]+dis[i][v])
#include <iostream>
using namespace std;

const int maxn = 1010;
int n;

int dis[maxn][maxn];

void Floyd()
{
    for (int i = 1; i <= n; ++i)         // 中转点
        for (int u = 1; u <= n; ++u)     // 起点
            for (int v = 1; v <= n; ++v) // 终点
                dis[u][v] = min(dis[u][v], dis[u][i] + dis[i][v]);
}
