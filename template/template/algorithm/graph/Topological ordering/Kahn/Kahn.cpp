// 将入度为0的点加入拓扑序并删除，不断重复此操作
#include <vector>
#include <queue>
using namespace std;

const int N = 1010;
int n;

int ind[N];
vector<int> G[N];
vector<int> ans;
bool Kahn()
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (ind[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ans.push_back(u);
        for (int v : G[u])
            if (--ind[v] == 0)
                q.push(v);
    }
    return ans.size() == n;
}