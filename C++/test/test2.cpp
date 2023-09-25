#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define int long long

const int N = 1e5 + 5;
int n, m;
vector<int> busRoute[N];
vector<int> ans;
struct Edge
{
    int to, next;
} edge[2 * N];

int head[2 * N], cnt;
bool vis[N];

void init()
{
    for (int i = 0; i < 2 * N; i++)
    {
        edge[i].next = -1;
        head[i] = -1;
    }
    cnt = 0;
}

void addEdge(int u, int v)
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int fa[N][20], deep[N];

void dfs(int x, int father)
{
    deep[x] = deep[father] + 1;
    fa[x][0] = father;
    for (int i = 1; (1ll << i) <= deep[x]; i++)
    {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; ~i; i = edge[i].next)
    {
        if (edge[i].to != father)
        {
            dfs(edge[i].to, x);
        }
    }
}

int LCA(int x, int y)
{
    if (deep[x] < deep[y])
    {
        swap(x, y);
    }
    for (int i = 19; i >= 0; i--)
    {
        if (deep[x] - (1ll << i) >= deep[y])
        {
            x = fa[x][i];
        }
    }
    if (x == y)
    {
        return x;
    }
    for (int i = 19; i >= 0; i--)
    {
        if (fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

void search(int u, int e, int num)
{
    int father = LCA(u, e);
    while (u != father)
    {
        ans[u] = min(ans[u], num);
        u = fa[u][0];
    }
    while (e != father)
    {
        ans[e] = min(ans[e], num);
        e = fa[e][0];
    }
    ans[father] = min(ans[father], num);
}

void solve()
{
    cin >> n >> m;
    ans.resize(n + 1, (int)1e9);
    init();
    for (int i = 1; i <= n - 1; i++)
    {
        int x;
        cin >> x;
        addEdge(x, i + 1);
        addEdge(i + 1, x);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        busRoute[x].push_back(y);
        busRoute[y].push_back(x);
    }
    queue<pair<int, int>> q;
    q.emplace(1, 0);
    while (!q.empty())
    {
        int u = q.front().first;
        int num = q.front().second;
        q.pop();
        vis[u] = 1;
        for (int e : busRoute[u])
        {
            if (!vis[e])
            {
                search(u, e, num + 1);
                q.emplace(e, num + 1);
            }
        }
    }
    for (int i = 2; i <= n; i++)
    {
        if (ans[i] == (int)1e9)
        {
            ans[i] = -1;
        }
        cout << ans[i] << " ";
    }
    cout << "\n";
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}