#include <bits/stdc++.h>
#define ls (pos << 1)
#define rs (pos << 1 | 1)
using namespace std;

const int N = 1e6 + 10;
int a[N], tree[N << 2];

void pushup(int pos)
{
    tree[pos] = max(tree[ls], tree[rs]);
}

void build_tree(int pos, int l, int r) // 建树
{
    if (l == r)
    {
        tree[pos] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(ls, l, mid);
    build_tree(rs, mid + 1, r);
    pushup(pos);
}

void change(int pos, int l, int r, int x, int y) // 单点修改
{
    if (l == r)
    {
        if (tree[pos] < y)
            tree[pos] = y;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        change(ls, l, mid, x, y);
    else
        change(rs, mid + 1, r, x, y); // 找询问的点在哪个节点上
    pushup(pos);
}

int query(int pos, int l, int r, int x, int y) // 区间询问
{
    if (x <= l && r <= y)
        return tree[pos];
    int mid = (l + r) >> 1, ans = -1e9;
    if (x <= mid)
        ans = max(ans, query(ls, l, mid, x, y)); // 询问的一部分在左儿子的管辖范围内
    if (y > mid)
        ans = max(ans, query(rs, mid + 1, r, x, y)); // 一部分在右儿子范围内
    return ans;
}