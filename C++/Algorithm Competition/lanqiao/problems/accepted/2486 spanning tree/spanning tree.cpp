#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u;
    int v;
    int dis;

    bool operator<(const Edge &a) const
    {
        return dis < a.dis;
    }
};

struct UFS
{
    std::vector<int> root;

    UFS(int n)
    {
        root.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            root[i] = i;
        }
    }

    int find(int x)
    {
        return x == root[x] ? root[x] : root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        int dx = find(x);
        int dy = find(y);
        if (dx == dy)
        {
            return;
        }
        root[dy] = dx;
    }
};

long long kruskal(int n, std::vector<Edge> &ed)
{
    std::sort(ed.begin(), ed.end());
    long long res = 0;
    int count = 0;
    UFS ufs(n);
    for (auto &x : ed)
    {
        if (ufs.find(x.u) == ufs.find(x.v))
        {
            continue;
        }
        ufs.merge(x.u, x.v);
        res += x.dis;
        if (++count == n - 1)
        {
            return res;
        }
    }
    return -1;
}

void solve()
{
    int n = 8;
    std::vector<Edge> ed;
    std::vector<std::vector<int>> graph = {
        {0, 9, 3, 0, 0, 0, 0, 9},
        {9, 0, 8, 1, 4, 0, 0, 0},
        {3, 8, 0, 9, 0, 0, 0, 0},
        {0, 1, 9, 0, 3, 0, 0, 5},
        {0, 4, 0, 3, 0, 7, 0, 6},
        {0, 0, 0, 0, 7, 0, 5, 2},
        {0, 0, 0, 0, 0, 5, 0, 4},
        {9, 0, 0, 5, 6, 2, 4, 0}};
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (graph[i - 1][j - 1] == 0)
            {
                continue;
            }
            ed.push_back(Edge{i, j, graph[i - 1][j - 1]});
        }
    }
    long long ans = kruskal(n, ed);
    std::cout << ans << std::endl;
}

int main()
{
    solve();
    return 0;
}