#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int N = 1e4 + 5;
const int M = 1e5 + 5;

struct edge
{
    int v;
    int length;
};
struct node
{
    int dis;
    int u;
    bool operator<(const node &a) const
    {
        return dis > a.dis;
    }
};
std::vector<std::vector<edge>> road;
std::priority_queue<node> q;
int dis[N * 3];
int vis[N * 3];

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push(node{0, s});
    while (!q.empty())
    {
        node k = q.top();
        q.pop();
        if (vis[k.u])
        {
            continue;
        }
        vis[k.u] = 1;
        for (auto ed : road[k.u])
        {
            if (dis[ed.v] > dis[k.u] + ed.length)
            {
                dis[ed.v] = dis[k.u] + ed.length;
                q.push(node{dis[ed.v], ed.v});
            }
        }
    }
}

void solve()
{
    int n, m;
    std::cin >> n >> m;
    road.resize(3 * n + 1);
    int a, b, c, d;
    for (int i = 1; i <= m; i++)
    {
        std::cin >> a >> b >> c >> d;
        if (d)
        {
            road[a].push_back(edge{b + n, c});
            road[b].push_back(edge{a + n, c});
            road[a + n].push_back(edge{b + n + n, c});
            road[b + n].push_back(edge{a + n + n, c});
        }
        else
        {
            road[a].push_back(edge{b, c});
            road[b].push_back(edge{a, c});
            road[a + n].push_back(edge{b + n, c});
            road[b + n].push_back(edge{a + n, c});
            road[a + n + n].push_back(edge{b + n + n, c});
            road[b + n + n].push_back(edge{a + n + n, c});
        }
    }
    dijkstra(1);
    std::cout << dis[n] - std::min(dis[3 * n], std::min(dis[2 * n], dis[n])) << std::endl;
}

int main()
{
    solve();
    return 0;
}