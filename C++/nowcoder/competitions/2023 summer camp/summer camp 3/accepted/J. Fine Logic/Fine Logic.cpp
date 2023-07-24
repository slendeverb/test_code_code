#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxn = 1e6 + 10;
const int maxm = 1e6 + 10;

int ind[maxn];
vector<int> G[maxn];
vector<int> ans;
int n, m;

bool kahn()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (ind[i] == 0)
        {
            q.push(i);
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ans.push_back(u);
        for (auto v : G[u])
        {
            if (--ind[v] == 0)
            {
                q.push(v);
            }
        }
    }
    return ans.size() == n;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        ind[v]++;
    }
    if (kahn())
    {
        cout << "1\n";
        for (int ele : ans)
        {
            cout << ele << ' ';
        }
        cout << "\n";
    }
    else // 如果有环,则直接输出1~n,n~1(这两个排列包含所有情况)
    {
        cout << "2\n";
        for (int i = 1; i <= n; i++)
        {
            cout << i << ' ';
        }
        cout << "\n";
        for (int i = n; i >= 1; i--)
        {
            cout << i << ' ';
        }
        cout << "\n";
    }
    return 0;
}