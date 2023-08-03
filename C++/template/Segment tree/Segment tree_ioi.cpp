#include <iostream>
#include <string>
using namespace std;

#define ls (pos << 1)
#define rs (pos << 1 | 1)

typedef long long ll;
const int N = 5e5 + 10;
int n, m;
char a[N];

struct Segment_tree
{
    ll i, o, io, oi, ioi;
    int l, r;
    inline void init()
    {
        i = o = io = oi = ioi = 0;
    }
} s[N << 2];

void pushup(Segment_tree &pos, Segment_tree x, Segment_tree y)
{
    pos.i = x.i + y.i;
    pos.o = x.o + y.o;
    pos.io = x.io + y.io + x.i * y.o;
    pos.oi = x.oi + y.oi + x.o * y.i;
    pos.ioi = x.ioi + y.ioi + x.i * y.oi + x.io * y.i;
}

void build_tree(int pos, int l, int r)
{
    s[pos].l = l;
    s[pos].r = r;
    if (l == r)
    {
        if (a[l] == 'I')
        {
            s[pos].i = 1;
        }
        else
        {
            s[pos].o = 1;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(ls, l, mid);
    build_tree(rs, mid + 1, r);
    pushup(s[pos], s[ls], s[rs]);
}

void ChangeIOI(int pos, int x, char c)
{
    if (s[pos].l == s[pos].r)
    {
        if (c == 'I')
        {
            s[pos].i = 1;
            s[pos].o = 0;
        }
        else
        {
            s[pos].i = 0;
            s[pos].o = 1;
        }
        return;
    }
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ChangeIOI(ls, x, c);
    else
        ChangeIOI(rs, x, c);
    pushup(s[pos], s[ls], s[rs]);
}

Segment_tree query(int pos, int x, int y)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        return s[pos];
    }
    int mid = (s[pos].l + s[pos].r) >> 1;
    Segment_tree ret, tmp;
    ret.init(), tmp.init();
    if (x <= mid)
    {
        tmp = query(ls, x, y);
        pushup(ret, ret, tmp);
    }
    if (y > mid)
    {
        tmp = query(rs, x, y);
        pushup(ret, ret, tmp);
    }
    return ret;
}

int main()
{
    cin >> n >> m;
    scanf("%s", a + 1);
    build_tree(1, 1, n);
    while (m--)
    {
        int opt, x, l, r;
        string s;
        cin >> opt;
        if (opt == 1)
        {
            cin >> x >> s;
            ChangeIOI(1, x, s[0]);
        }
        else if (opt == 2)
        {
            cin >> l >> r;
            cout << query(1, l, r).ioi << "\n";
        }
    }
    return 0;
}