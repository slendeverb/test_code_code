#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

struct Edge
{
    int to, next;
} edge[N << 1];

std::vector<int> v[N], w[N];
int fa[N][31], cost[N][31], dep[N], n, m, a, b, c;

// dfs，用来为 lca 算法做准备。接受两个参数：dfs 起始节点和它的父亲节点。
void dfs(int root, int fno)
{
    // 初始化：第 2^0 = 1 个祖先就是它的父亲节点，dep 也比父亲节点多 1。
    fa[root][0] = fno;
    dep[root] = dep[fa[root][0]] + 1;
    // 初始化：其他的祖先节点：第 2^i 的祖先节点是第 2^(i-1) 的祖先节点的第 2^(i-1) 的祖先节点。
    for (int i = 1; i < 31; ++i)
    {
        fa[root][i] = fa[fa[root][i - 1]][i - 1];
        cost[root][i] = cost[fa[root][i - 1]][i - 1] + cost[root][i - 1];
    }
    // 遍历子节点来进行 dfs。
    int sz = v[root].size();
    for (int i = 0; i < sz; ++i)
    {
        if (v[root][i] == fno)
            continue;
        cost[v[root][i]][0] = w[root][i];
        dfs(v[root][i], root);
    }
}

// lca。用倍增算法算取 x 和 y 的 lca 节点。
int lca(int x, int y)
{
    // 令 y 比 x 深。
    if (dep[x] > dep[y])
        swap(x, y);
    // 令 y 和 x 在一个深度。
    int tmp = dep[y] - dep[x], ans = 0;
    for (int j = 0; tmp; ++j, tmp >>= 1)
        if (tmp & 1)
            ans += cost[y][j], y = fa[y][j];
    // 如果这个时候 y = x，那么 x，y 就都是它们自己的祖先。
    if (y == x)
        return ans; // return y;
    // 不然的话，找到第一个不是它们祖先的两个点。
    for (int j = 30; j >= 0 && y != x; --j)
    {
        if (fa[x][j] != fa[y][j])
        {
            ans += cost[x][j] + cost[y][j];
            x = fa[x][j];
            y = fa[y][j];
        }
    }
    // 返回结果。
    ans += cost[x][0] + cost[y][0];
    return ans; // return fa[y][0];
}

int main()
{
    // 初始化表示祖先的数组 fa，代价 cost 和深度 dep。
    memset(fa, 0, sizeof(fa));
    memset(cost, 0, sizeof(cost));
    memset(dep, 0, sizeof(dep));
    // 读入树：节点数一共有 n 个。
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d %d %d", &a, &b, &c);
        v[a].push_back(b);
        v[b].push_back(a);
        w[a].push_back(c);
        w[b].push_back(c);
    }
    // 为了计算 lca 而使用 dfs。
    dfs(1, 0);
    // 查询 m 次，每一次查找两个节点的 lca 点。
    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d", &a, &b);
        printf("%d\n", lca(a, b));
    }
    return 0;
}

//

// struct Edge
// {
//     int v;
//     std::shared_ptr<Edge> next{nullptr};

//     Edge(int v) : v{v} {}
// };

// struct VillageNode
// {
//     int depth;
//     std::shared_ptr<Edge> firstEdge;
//     int father[20];
// };

// class Graph
// {
//     int vertexNum;
//     int edgeNum;
//     std::unique_ptr<VillageNode[]> village;

// public:
//     Graph(int n)
//     {
//         vertexNum = n;
//         edgeNum = n - 1;
//         village = std::make_unique<VillageNode[]>(vertexNum);
//     }

//     void create()
//     {
//         int u, v;
//         std::shared_ptr<Edge> p, q;
//         for (int i = 0; i < edgeNum; i++)
//         {
//             std::cin >> u >> v;
//             p = std::make_shared<Edge>(u);
//             q = std::make_shared<Edge>(v);
//             if (village[u].firstEdge == nullptr)
//             {
//                 village[u].firstEdge = q;
//             }
//             else
//             {
//                 auto tmp = village[u].firstEdge;
//                 while (tmp->next != nullptr)
//                 {
//                     tmp = tmp->next;
//                 }
//                 tmp->next = q;
//             }
//             if (village[v].firstEdge == nullptr)
//             {
//                 village[v].firstEdge = p;
//             }
//             else
//             {
//                 auto tmp = village[v].firstEdge;
//                 while (tmp->next != nullptr)
//                 {
//                     tmp = tmp->next;
//                 }
//                 tmp->next = p;
//             }
//         }
//     }

//     void BFS()
//     {
//         Queue<int> q;
//         village[0].depth = 0;
//         village[0].father[0] = 0;
//         q.push(0);
//         while (!q.empty())
//         {
//             int u = q.front();
//             q.pop();
//             for (int i = 1; i < 20; i++) // u的第2^i个父亲结点等于u的第2^(i-1)个父亲结点的第2^(i-1)个父亲结点
//             {
//                 village[u].father[i] = village[village[u].father[i - 1]].father[i - 1];
//             }
//             std::shared_ptr<Edge> p;
//             for (p = village[u].firstEdge; p != nullptr; p = p->next)
//             {
//                 int v = p->v;
//                 if (v == village[u].father[0]) // 因为存储的是双向边，所以防止再访问到已经访问过的父亲结点
//                 {
//                     continue;
//                 }
//                 village[v].depth = village[u].depth + 1;
//                 village[v].father[0] = u;
//                 q.push(v);
//             }
//         }
//     }

//     int LCA(int u, int v)
//     {
//         if (village[u].depth > village[v].depth)
//         {
//             std::swap(u, v);
//         }
//         int depthDifference = village[v].depth - village[u].depth;
//         int du = u, dv = v;
//         for (int i = 0; depthDifference; depthDifference >>= 1, i++)
//         {
//             if (depthDifference & 1)
//             {
//                 dv = village[dv].father[i];
//             }
//         }
//         if (dv == du)
//         {
//             return du;
//         }
//         for (int i = 19; i >= 0; i--) // 不在同一结点却在同一深度，那就两个结点一起往上跳2^i单位
//         {
//             if (village[du].father[i] == village[dv].father[i]) // 如果会跳过了，则跳过这一步跳跃
//             {
//                 continue;
//             }
//             du = village[du].father[i];
//             dv = village[dv].father[i];
//         }
//         return village[du].father[0];
//     }

//     bool inPath(int a, int b, int c)
//     {
//         int vertexInAB = LCA(a, b);
//         int endPointOfAC = LCA(a, c);
//         int endPointOfBC = LCA(b, c);
//         if (endPointOfAC == c && endPointOfBC == c) // 如果endPointOfAC == c并且endPointOfBC == c，说明c结点是a和b的公共祖先
//         {
//             if (vertexInAB == c) // 如果vertexInAB == c，说明c就是a和b的最近公共祖先,c必定在a和b的路径上
//             {
//                 return true;
//             }
//             else // 如果vertexInAB != c，说明c不是a和b的最近公共祖先，a和b的路径上不包括c
//             {
//                 return false;
//             }
//         }
//         else if (endPointOfAC == c || endPointOfBC == c) // c是a的祖先或者是b的祖先，说明c在a到vertexInAB的路径上或者在b到vertexInAB的路径上
//         {
//             return true; // 此时c一定是a和b路径上的点
//         }
//         else
//         {
//             return false; // 如果c不是a的祖先，也不是b的祖先，则a和b的路径上不会经过c点
//         }
//     }
// };