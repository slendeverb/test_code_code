#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 2021;
const int M = 2021 * 2020 / 2;

struct edge
{
    int u;
    int v;
    int length;
    bool operator<(const edge &a) const
    {
        return length < a.length;
    }
};
std::vector<edge> polis;

struct UFS
{
    int root[N + 1];
    UFS()
    {
        for (int i = 1; i <= N; i++)
        {
            root[i] = i;
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
        int dx = find(x);
        int dy = find(y);
        if (dx == dy)
        {
            return;
        }
        root[dy] = dx;
    }
};

int distance(int a, int b)
{
    int res = 0;
    while (a || b)
    {
        if (a % 10 != b % 10)
        {
            res += a % 10;
            res += b % 10;
        }
        a /= 10;
        b /= 10;
    }
    return res;
}

long long kruskal()
{
    std::sort(polis.begin(), polis.end());
    UFS ufs;
    long long res = 0;
    long long count = 0;
    for (int i = 0; i < polis.size(); i++)
    {
        if (ufs.find(polis[i].u) == ufs.find(polis[i].v))
        {
            continue;
        }
        ufs.merge(polis[i].u, polis[i].v);
        res += polis[i].length;
        if (++count == N - 1)
        {
            return res;
        }
    }
    return -1;
}

void solve()
{
    int n = N;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            polis.push_back(edge{i, j, distance(i, j)});
        }
    }
    long long ans = kruskal();
    std::cout << ans << std::endl;
}

int main()
{
    solve();
    return 0;
}