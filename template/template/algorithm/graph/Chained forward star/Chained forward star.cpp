#include <iostream>
using namespace std;

// 链式前向星的存储结构：
// 以静态一维结构体数组存储所有边，结构体内保存边的终点v，边权w以及与起点相关的链信息next
// 所有边在一维结构体数组edge中是无序排列的，tot是边的总数
// head数组记录了每个节点的链头信息
const int MAXN = 10000;
struct Edge
{
    int v, w, next;
} edge[MAXN * MAXN];
int tot;
int head[MAXN];

// 插入一条起点为u，终点为v，权值为w的边。
// 将当前edge数组下一个没有使用的（下标为tot的）元素的v和w进行赋值
// 对于起点u，首先让当前元素的next指针向前指向前一个代表起点为u的表头元素（其下标存在head[u]中），
// 然后将当前的下标tot设置为起点为u的表头位置head[u]=tot，最后令tot加1，完成操作等待接收下一输入
void AddEdge(int u, int v, int w)
{
    // 建边
    edge[tot].v = v;
    edge[tot].w = w;
    // 连边
    edge[tot].next = head[u];
    head[u] = tot++;
}

// “前向”的名字由来是因为插入过程中类似于链表的表头插入，因此如果按照插入顺序来看，表头是在后端而不是前端，查找的时候可以想象成从后往前查找，故称“前向”
// 从下标为head[u]的edge数组元素开始，不断通过next前向查找，直到next为空
// 适合遍历某一特定起点的所有边，不适合快速获得特定边的信息
int main()
{
    int u;
    cin >> u;
    for (int i = head[u]; ~i; i = edge[i].next)
    {
        cout << edge[i].v << " " << edge[i].w << "\n";
    }
}
