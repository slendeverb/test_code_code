#include <iostream>
#include <algorithm>
using namespace std;

#define ls (pos << 1)
#define rs (pos << 1 | 1)
#define int long long

const int N = 1e5 + 5;
const int NUM = 21;
int n, m, a[N];

struct Segment_tree
{
    int l, r;
    int tag, num[2][25];
} s[N << 2];

void pushup(int pos)
{
    for (int i = 0; i < NUM; i++)
    {
        s[pos].num[1][i] = s[ls].num[1][i] + s[rs].num[1][i];
        s[pos].num[0][i] = s[ls].num[0][i] + s[rs].num[0][i];
    }
}

void pushdown(int pos)
{
    if (s[pos].l == s[pos].r)
    {
        return;
    }
    s[ls].tag ^= s[pos].tag;
    s[rs].tag ^= s[pos].tag;
    for (int i = 0; i < NUM; i++)
    {
        if (s[pos].tag & (1 << i))
        {
            swap(s[ls].num[0][i], s[ls].num[1][i]);
            swap(s[rs].num[0][i], s[rs].num[1][i]);
        }
    }
    s[pos].tag = 0;
}

void build_tree(int pos, int l, int r)
{
    s[pos].l = l;
    s[pos].r = r;
    if (l == r)
    {
        for (int i = 0; i < NUM; i++)
        {
            s[pos].num[a[l] & (1 << i) ? 1 : 0][i]++;
        }
        s[pos].tag = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(ls, l, mid);
    build_tree(rs, mid + 1, r);
    pushup(pos);
}

void ChangeXOR(int pos, int x, int y, int k)
{
    pushdown(pos);
    if (x <= s[pos].l && s[pos].r <= y)
    {
        for (int i = 0; i < NUM; i++)
        {
            if (k & (1 << i))
            {
                swap(s[pos].num[0][i], s[pos].num[1][i]);
            }
        }
        s[pos].tag = k;
        return;
    }
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ChangeXOR(ls, x, y, k);
    if (y > mid)
        ChangeXOR(rs, x, y, k);
    pushup(pos);
}

int query(int pos, int x, int y)
{
    pushdown(pos);
    if (x <= s[pos].l && s[pos].r <= y)
    {
        int ret = 0;
        for (int i = 0; i < NUM; i++)
        {
            ret += (1 << i) * s[pos].num[1][i];
        }
        return ret;
    }
    int ret = 0;
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ret += query(ls, x, y);
    if (y > mid)
        ret += query(rs, x, y);
    return ret;
}