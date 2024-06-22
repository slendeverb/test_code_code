#include <iostream>
#include <cstdio>
using namespace std;

#define ls (pos << 1)
#define rs (pos << 1 | 1)
typedef long long ll;

const int MAXN = 1e6 + 10;
int mod = 998244353;
int n, m;
int a[MAXN];

struct Segment_Tree
{
    ll sum, add, mul;
    int l, r;
} s[MAXN << 2];

void pushup(int pos)
{
    s[pos].sum = (s[ls].sum + s[rs].sum) % mod;
    return;
}

void pushdown(int pos)
{
    // pushdown的维护
    s[ls].sum = (s[ls].sum * s[pos].mul + s[pos].add * (s[ls].r - s[ls].l + 1)) % mod;
    s[rs].sum = (s[rs].sum * s[pos].mul + s[pos].add * (s[rs].r - s[rs].l + 1)) % mod;

    s[ls].mul = (s[ls].mul * s[pos].mul) % mod;
    s[rs].mul = (s[rs].mul * s[pos].mul) % mod;

    s[ls].add = (s[ls].add * s[pos].mul + s[pos].add) % mod;
    s[rs].add = (s[rs].add * s[pos].mul + s[pos].add) % mod;

    s[pos].add = 0;
    s[pos].mul = 1;
    return;
}

void build_tree(int pos, int l, int r)
{
    // 建树
    s[pos].l = l;
    s[pos].r = r;
    s[pos].mul = 1;

    if (l == r)
    {
        s[pos].sum = a[l] % mod;
        return;
    }

    int mid = (l + r) >> 1;
    build_tree(ls, l, mid);
    build_tree(rs, mid + 1, r);
    pushup(pos);
    return;
}

void ChangeMul(int pos, int x, int y, int k)
{
    // 区间乘法
    if (x <= s[pos].l && s[pos].r <= y)
    {
        s[pos].add = (s[pos].add * k) % mod;
        s[pos].mul = (s[pos].mul * k) % mod;
        s[pos].sum = (s[pos].sum * k) % mod;
        return;
    }

    pushdown(pos);
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ChangeMul(ls, x, y, k);
    if (y > mid)
        ChangeMul(rs, x, y, k);
    pushup(pos);
    return;
}

void ChangeAdd(int pos, int x, int y, int k)
{
    // 区间加法
    if (x <= s[pos].l && s[pos].r <= y)
    {
        s[pos].add = (s[pos].add + k) % mod;
        s[pos].sum = (s[pos].sum + k * (s[pos].r - s[pos].l + 1)) % mod;
        return;
    }

    pushdown(pos);
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ChangeAdd(ls, x, y, k);
    if (y > mid)
        ChangeAdd(rs, x, y, k);
    pushup(pos);
    return;
}

ll query(int pos, int x, int y)
{
    // 区间询问
    if (x <= s[pos].l && s[pos].r <= y)
    {
        return s[pos].sum;
    }

    pushdown(pos);
    ll val = 0;
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        val = (val + query(ls, x, y)) % mod;
    if (y > mid)
        val = (val + query(rs, x, y)) % mod;
    return val;
}