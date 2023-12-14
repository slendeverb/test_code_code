#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 2010;

struct node
{
    int val, pos;
    bool operator<(const node &a) const
    {
        return val < a.val;
    }
};

int a[maxn][maxn];
vector<int> v;
priority_queue<node> q[maxn];
bool vis[maxn];

void init(int n, int m)
{
    v.clear();
    for (int i = 1; i <= n; i++)
    {
        while (!q[i].empty())
        {
            q[i].pop();
        }
    }
    for (int i = 1; i <= m; i++)
    {
        vis[i] = 0;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, k;
        cin >> n >> m >> k;
        init(n, m);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> a[i][j];
                q[i].push({a[i][j], j});
            }
        }
        while (k--)
        {
            int x = (k + 1) % n;
            if (x == 0)
            {
                x = n;
            }
            while (vis[q[x].top().pos])
            {
                q[x].pop();
            }
            v.push_back(q[x].top().pos);
            vis[q[x].top().pos] = 1;
            q[x].pop();
        }
        sort(v.begin(), v.end());
        for (auto element : v)
        {
            cout << element << " ";
        }
        cout << "\n";
    }
    return 0;
}