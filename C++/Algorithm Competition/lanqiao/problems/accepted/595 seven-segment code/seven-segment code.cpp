#include <iostream>
using namespace std;

// 用 1 ~ 7 来代表 a ~ g；
// 若某两个二极管相邻，那么就在它们之间连一条边；
// 先用 dfs 枚举出二极管的所有亮灭情况；
// 再用 并查集 判断是否只有一个连通块；

const int N = 10;

int ans;
int p[N];
bool st[N];
int e[N][N];

int find(int x)
{
    if (p[x] != x)
        p[x] = find(p[x]);
    return p[x];
}

void dfs(int u)
{
    if (u == 8)
    {
        for (int i = 1; i <= 7; i++)
            p[i] = i;

        for (int i = 1; i <= 7; i++)
            for (int j = 1; j <= 7; j++)
                if (e[i][j] && st[i] && st[j])
                    p[find(i)] = find(j);

        int cnt = 0;
        for (int i = 1; i <= 7; i++)
            if (st[i] && p[i] == i)
                cnt++;

        if (cnt == 1)
            ans++;
        return;
    }

    st[u] = 1; // 打开第 u 个二极管
    dfs(u + 1);

    st[u] = 0; // 关闭第 u 个二极管
    dfs(u + 1);
}

int main()
{
    e[1][2] = e[1][6] = 1;
    e[2][1] = e[2][7] = e[2][3] = 1;
    e[3][2] = e[3][7] = e[3][4] = 1;
    e[4][3] = e[4][5] = 1;
    e[5][4] = e[5][7] = e[5][6] = 1;
    e[6][1] = e[6][7] = e[6][5] = 1;
    e[7][2] = e[7][3] = e[7][5] = e[7][6] = 1;

    dfs(1);

    cout << ans << endl;
    return 0;
}