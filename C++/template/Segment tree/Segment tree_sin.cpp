#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define ls (pos << 1)
#define rs (pos << 1 | 1)

typedef long long ll;
const int N = 2e5 + 10;
int a[N];

struct Segment_tree
{
    double sin, cos;
    ll add;
    int l, r;
} s[N << 2];

void pushup(int pos)
{
    s[pos].sin = s[ls].sin + s[rs].sin;
    s[pos].cos = s[ls].cos + s[rs].cos;
}

void update(int pos, double sinx, double cosx)
{
    double sin_copy = s[pos].sin, cos_copy = s[pos].cos;
    s[pos].sin = sin_copy * cosx + cos_copy * sinx;
    s[pos].cos = cos_copy * cosx - sin_copy * sinx;
}

void pushdown(int pos)
{
    if (!s[pos].add)
    {
        return;
    }
    double sinx = sin(s[pos].add), cosx = cos(s[pos].add);
    update(ls, sinx, cosx);
    update(rs, sinx, cosx);
    s[ls].add = s[ls].add + s[pos].add;
    s[rs].add = s[rs].add + s[pos].add;
    s[pos].add = 0;
}

void build_tree(int pos, int l, int r)
{
    s[pos].l = l;
    s[pos].r = r;
    if (l == r)
    {
        s[pos].sin = sin(a[l]);
        s[pos].cos = cos(a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(ls, l, mid);
    build_tree(rs, mid + 1, r);
    pushup(pos);
}

void ChangeAdd(int pos, int x, int y, int k)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        update(pos, sin(k), cos(k));
        s[pos].add = s[pos].add + k;
        return;
    }
    pushdown(pos);
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ChangeAdd(ls, x, y, k);
    if (y > mid)
        ChangeAdd(rs, x, y, k);
    pushup(pos);
}

double query(int pos, int x, int y)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        return s[pos].sin;
    }
    pushdown(pos);
    double ret = 0.0;
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ret += query(ls, x, y);
    if (y > mid)
        ret += query(rs, x, y);
    return ret;
}