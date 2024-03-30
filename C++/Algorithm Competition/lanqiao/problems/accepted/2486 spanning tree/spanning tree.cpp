#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// struct Edge
// {
//     int u;
//     int v;
//     int dis;

//     bool operator<(const Edge &a) const
//     {
//         return dis < a.dis;
//     }
// };

// struct UFS
// {
//     std::vector<int> root;

//     UFS(int n)
//     {
//         root.resize(n + 1);
//         for (int i = 0; i <= n; i++)
//         {
//             root[i] = i;
//         }
//     }

//     int find(int x)
//     {
//         return x == root[x] ? root[x] : root[x] = find(root[x]);
//     }

//     void merge(int x, int y)
//     {
//         int dx = find(x);
//         int dy = find(y);
//         if (dx == dy)
//         {
//             return;
//         }
//         root[dy] = dx;
//     }
// };

// long long kruskal(int n, std::vector<Edge> &ed)
// {
//     std::sort(ed.begin(), ed.end());
//     long long res = 0;
//     int count = 0;
//     UFS ufs(n);
//     for (auto &x : ed)
//     {
//         if (ufs.find(x.u) == ufs.find(x.v))
//         {
//             continue;
//         }
//         ufs.merge(x.u, x.v);
//         res += x.dis;
//         if (++count == n - 1)
//         {
//             return res;
//         }
//     }
//     return -1;
// }

// void solve()
// {
//     int n = 8;
//     std::vector<Edge> ed;
//     int x = 0;
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= n; j++)
//         {
//             std::cin >> x;
//             if (x == 0)
//             {
//                 continue;
//             }
//             ed.push_back(Edge{i, j, x});
//         }
//     }
//     long long ans = kruskal(n, ed);
//     std::cout << ans << std::endl;
// }

int main()
{
    // solve();
    std::cout << 26 << std::endl; // 没有输入
    return 0;
}