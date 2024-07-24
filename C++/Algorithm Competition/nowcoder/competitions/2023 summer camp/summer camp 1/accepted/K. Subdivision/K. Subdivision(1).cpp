#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

const int maxn = 1e5 + 10;
const int inf = 0x3f3f3f3f;

struct edge
{
    int v, w;
};

struct node
{
    int dis, u;
    bool operator>(const node &a) const
    {
        return dis > a.dis;
    }
};

vector<edge> e[maxn];
int dis[maxn], vis[maxn];
priority_queue<node, vector<node>, greater<node>> q;

long long dijkstra(int n, int s, int k)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    q.push({0, s});
    while (!q.empty())
    {
        int u = q.top().u;
        q.pop();
        if (dis[u] == 0x3f3f3f3f)
        {
            continue;
        }
        for (auto ed : e[u])
        {
            int v = ed.v, w = ed.w;
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
    long long count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dis[i] <= k)
        {
            count++;
            if (i != 1)
            {
                count += (k - dis[i]);
            }
        }
    }
    return count;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    int count = 0;
    vis[1] = 1;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back({v, 1});
        e[v].push_back({u, 1});
    }
    long long ans = dijkstra(n, 1, k);
    cout << ans << "\n";
    return 0;
}