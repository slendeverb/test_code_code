#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e3 + 10;
const int maxn = 2e5 + 10;
int n, m;

struct Edge
{
    long long x, y, z;
    bool operator<(const Edge &edge) const
    {
        return z < edge.z;
    }
} e[maxn];

struct Ufs
{
    long long root[N], num[N];
    void init()
    {
        for (int i = 1; i <= n; i++)
        {
            root[i] = i;
            num[i] = 1;
        }
    }
    int find(int x)
    {
        if (root[x] != x)
        {
            return root[x] = find(root[x]);
        }
        return root[x];
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
        {
            return;
        }
        if (num[x] < num[y])
        {
            swap(x, y);
        }
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
        if (ufs.find(e[i].x) == ufs.find(e[i].y))
        {
            continue;
        }
        ufs.merge(e[i].x, e[i].y);
        ret += e[i].z;
        if (++cnt == n - 1)
        {
            return ret;
        }
    }
    return -1;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> e[i].x >> e[i].y >> e[i].z;
    }
    long long ans = Kruskal();
    if (ans == -1)
    {
        cout << "orz\n";
    }
    else
    {
        cout << ans << "\n";
    }
    return 0;
}