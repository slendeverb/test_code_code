int cnt = -1, u;
const int N = 1000;
int nxt[N], head[N], to[N];
// head[u] 和 cnt 的初始值都为 -1
void add(int u, int v)
{
    nxt[++cnt] = head[u]; // 当前边的后继
    head[u] = cnt;        // 起点 u 的第一条边
    to[cnt] = v;          // 当前边的终点
}
// 遍历 u 的出边
int main()
{
    for (int i = head[u]; ~i; i = nxt[i]) // ~i 表示 i != -1
    {
        int v = to[i];
    }
}
