#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n, k1, k2, num, flag, a[25], b[25], vis[25][25], s[600];
const int v[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
// 必须从右边开始找，因为答案可能有多种，输出最小编号序的答案;
void dfs(int x, int y, int k)  // 常规dfs搜索模板;
{
    if (x < 1 || y < 1 || x > n || y > n)
        return;  // 判断越界;
    if (b[x] < 0 || a[y] < 0 || flag == 1)
        return;  // 不符合题意或找到答案了就返回;
    s[k] =
        (x - 1) * n + (y - 1);  // 记录路径，(编号可用坐标表示为i*m+j，m为列数);
    if (x == n && y == n && k1 == 1 && k2 == 1)  // 找到答案就返回;
    {
        flag = 1;
        num = k;
        return;
    }
    for (int i = 0; i < 4; i++)  // 查找右左下上;
    {
        int xx = x + v[i][0];
        int yy = y + v[i][1];
        if (vis[xx][yy] == 1)
            continue;  // 该点走过，跳过;
        b[xx]--;
        a[yy]--;
        k1--;
        k2--;
        vis[xx][yy] = 1;
        dfs(xx, yy, k + 1);
        b[xx]++;  // 回溯，还原值;
        a[yy]++;
        k1++;
        k2++;
        vis[xx][yy] = 0;
    }
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        k1 += a[i];  // 记录每列可走的总数;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        k2 += b[i];  // 记录每行可走的总数;
    }
    flag = 0;
    vis[1][1] = 1;
    dfs(1, 1, 1);
    for (int i = 1; i <= num; i++)  // 从头遍历一遍，输出编号;
        cout << s[i] << " ";
    return 0;
}