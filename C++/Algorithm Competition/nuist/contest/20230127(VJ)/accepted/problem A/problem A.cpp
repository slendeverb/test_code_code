#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;

const int maxn = 760;
const int INF = 0x3f3f3f3f;

int map[maxn][maxn];
int dis[maxn];
int vis[maxn];
int Edge[maxn];

struct node
{
    int x;
    int y;
} Point[maxn];

int N, M;

void Prim()
{
    for (int i = 1; i < N; i++)
    {
        int minn = INF;
        int point_minn;
        for (int j = 1; j <= N; j++)
        {
            if (vis[j] == 0 && minn > dis[j])
            {
                minn = dis[j];
                point_minn = j;
            }
        }
        vis[point_minn] = 1;
        for (int k = 1; k <= N; k++)
        {
            if (vis[k] == 0 && dis[k] > map[point_minn][k])
            {
                Edge[k] = point_minn;
                dis[k] = map[point_minn][k];
            }
        }
        if (map[Edge[point_minn]][point_minn])
        {
            printf("%d %d\n", Edge[point_minn], point_minn);
        }
    }
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d%d", &Point[i].x, &Point[i].y);
        for (int j = 1; j < i; j++)
            map[i][j] = map[j][i] = (Point[i].x - Point[j].x) * (Point[i].x - Point[j].x) + (Point[i].y - Point[j].y) * (Point[i].y - Point[j].y);
        map[i][i] = INF;
    }
    scanf("%d", &M);
    int x, y;
    while (M--)
    {
        scanf("%d%d", &x, &y);
        map[x][y] = map[y][x] = 0;
    }
    memset(vis, 0, sizeof(vis));
    vis[1] = 1;
    for (int i = 1; i <= N; i++)
    {
        dis[i] = map[i][1];
        Edge[i] = 1;
    }
    Prim();
    return 0;
}