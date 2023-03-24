#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 800;
int root[N], n, m;

struct Point
{
    double x, y;
} point[N];

struct Edge
{
    int u, v;
    double w;
} edge[N * N];

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

double dis(Point a, Point b)
{
    return (a.x - b.x, 2) * (a.x - b.x, 2) + (a.y - b.y, 2) * (a.y - b.y, 2);
}

void initset()
{
    for (int i = 1; i <= n; ++i)
    {
        root[i] = i;
    }
}

int find(int a)
{
    return root[a] == a ? a : root[a] = find(root[a]);
}

int merge(int a, int b)
{
    int pa = find(a);
    int pb = find(b);
    if (pa != pb)
    {
        root[pb] = pa;
        return 1;
    }
    return 0;
}

void Kruskal()
{
    int k = 0;
    for (int i = 1; i < n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            edge[k].u = i;
            edge[k].v = j;
            edge[k].w = dis(point[i], point[j]);
            k++;
        }
    }
    sort(edge + 1, edge + k + 1, cmp);
    int cnt = 0;
    for (int i = 1; i <= k; ++i)
    {
        if (find(edge[i].u) != find(edge[i].v))
        {
            merge(edge[i].u, edge[i].v);
            cnt++;
            cout << edge[i].u << " " << edge[i].v << "\n";
        }
        if (cnt == n - 1)
        {
            break;
        }
    }
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    initset();
    for (int i = 1; i <= n; ++i)
    {
        cin >> point[i].x >> point[i].y;
    }
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        merge(x, y);
    }
    Kruskal();
    return 0;
}