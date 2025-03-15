#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
// 普利姆，注意建图技巧
const int maxn = 751;
const int INF = 0x3f3f3f3f;
int map[maxn][maxn];
int dis[maxn];
int vis[maxn];
int Edge[maxn]; // i到Edge[i]是一条生成树内的边
struct node
{
    int x;
    int y;
} Point[maxn]; // 第i个点的坐标
int N;         // 点的数量
int M;         // 更新边的数量
void init()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) // 建图
    {
        scanf("%d%d", &Point[i].x, &Point[i].y);
        for (int j = 1; j < i; j++) // 为什么这里不取sqrt，因为完全没必要
            map[i][j] = map[j][i] = (Point[i].x - Point[j].x) * (Point[i].x - Point[j].x) + (Point[i].y - Point[j].y) * (Point[i].y - Point[j].y);
        map[i][i] = INF; // 自己不可能到自己
    }
    scanf("%d", &M);
    int x, y;
    while (M--) // 更新图
    {
        scanf("%d%d", &x, &y);
        map[x][y] = map[y][x] = 0;
    }
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    for (int i = 1; i <= N; i++)
    {
        dis[i] = map[i][1];
        Edge[i] = 1; // 初始化为存储i到1的边
    }
}
void Prim()
{
    for (int i = 1; i < N; i++)
    {
        int minn = INF;
        int point_minn;
        for (int j = 1; j <= N; j++)
            if (vis[j] == 0 && minn > dis[j])
            {
                minn = dis[j];
                point_minn = j;
            }
        vis[point_minn] = 1;
        for (int k = 1; k <= N; k++)
            if (vis[k] == 0 && dis[k] > map[point_minn][k])
            {
                Edge[k] = point_minn; // 这里是输出方式的技巧
                dis[k] = map[point_minn][k];
            }
        if (map[Edge[point_minn]][point_minn])
            printf("%d %d\n", Edge[point_minn], point_minn);
    }
}
int main()
{
    init();
    Prim();
    return 0;
}