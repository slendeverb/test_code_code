#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> G(n + 1);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<int> dis(n + 1, -1);
    vector<int> parent(n + 1);
    vector<int> inner(n + 1);
    queue<int> q;
    q.push(1);
    dis[1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : G[u])
        {
            if (dis[v] != -1)
            {
                continue;
            }
            q.push(v);
            dis[v] = dis[u] + 1;
            parent[v] = u;
            inner[u] = 1;
        }
    }

    long long ans = 1;
    for (int u = 2; u <= n; u++)
    {
        if (dis[u] == -1 || dis[u] > k)
        {
            continue;
        }
        long long cnt = 0;
        for (auto v : G[u])
        {
            if (v == parent[u] || u == parent[v])
            {
                continue;
            }
            cnt++;
        }
        if (!inner[u])
        {
            cnt = max(cnt, 1ll);
        }
        ans += (k - dis[u]) * cnt + 1;
    }

    cout << ans << "\n";
    return 0;
}