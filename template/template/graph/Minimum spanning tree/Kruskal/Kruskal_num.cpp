// 将边按边权从小到大排序，依次考虑每条边，能加入就加入
// 用并查集维护即可
#include <algorithm>
using namespace std;

const int N = 5e3 + 10;
int n, m;

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &edge) const { return w < edge.w; }
} e[N];

struct Ufs
{
    int root[N], num[N];
    void init()
    {
        for (int i = 1; i <= n; ++i)
        {
            root[i] = i;
            num[i] = 1;
        }
    }
    int find(int x)
    {
        if (root[x] != x)
            return root[x] = find(root[x]);
        return root[x];
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (num[x] < num[y])
            swap(x, y);
        root[y] = x;
        num[x] += num[y];
    }
} ufs;

long long Kruskal()
{
    sort(e + 1, e + 1 + m);
    ufs.init();
    long long ret = 0, cnt = 0;
    for (int i = 1; i <= m; i++)
    {
        if (ufs.find(e[i].u) == ufs.find(e[i].v))
        {
            continue;
        }
        ufs.merge(e[i].u, e[i].v);
        ret += e[i].w;
        if (++cnt == n - 1)
        {
            return ret;
        }
    }
    return -1;
}
