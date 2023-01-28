#include <iostream>
#include <queue>
#include <climits>
using namespace std;

const int N = 1e5 + 10;
const int maxn = 1e6 + 10;

struct Edge
{
    int from, to, len, nxt;
} e[maxn];

struct Node
{
    int v;
    long long dis;
    bool operator<(const Node &node) const
    {
        return dis > node.dis;
    }
};

priority_queue<Node> q;

int head[N], ans[N], pos[N];
long long dis[N];

int n, m, cnt, flag;

void add(int a, int b, int w)
{
    e[++cnt].from = a;
    e[cnt].to = b;
    e[cnt].len = w;
    e[cnt].nxt = head[a];
    head[a] = cnt;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        add(a, b, w);
        add(b, a, w);
    }
    for (int i = 1; i <= n; i++)
    {
        dis[i] = LLONG_MAX;
    }
    int start = 1;
    dis[start] = 0;
    ans[flag] = start;
    q.push({start, dis[start]});
    while (!q.empty())
    {
        Node tmp = q.top();
        q.pop();
        int k = tmp.v;
        if (tmp.dis != dis[k])
        {
            continue;
        }
        for (int i = head[k]; i; i = e[i].nxt)
        {
            if (dis[e[i].to] > dis[k] + e[i].len)
            {
                dis[e[i].to] = dis[k] + e[i].len;
                q.push({e[i].to, dis[e[i].to]});
                pos[e[i].to] = k;
            }
        }
    }
    bool can_find_start_point = false;
    for (int i = n; i; i = pos[i])
    {
        ans[++flag] = i;
        if (i == 1)
        {
            can_find_start_point = true;
        }
    }
    if (!can_find_start_point)
    {
        cout << -1 << "\n";
    }
    else
    {
        for (int i = flag; i >= 1; i--)
        {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}