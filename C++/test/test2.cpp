#include <cmath>
#define ls (pos << 1)
#define rs (pos << 1 | 1)
#define mid ((l + r) >> 1)

const int N = 2e5 + 10;
int a[N];
double sink, cosk;

struct Segment_Tree
{
    double sine[N << 2], cosi[N << 2];
    long long tag[N << 2];

    inline void pushup(int pos)
    {
        sine[pos] = sine[ls] + sine[rs];
        cosi[pos] = cosi[ls] + cosi[rs];
    }

    inline void update(int pos, double sinx, double cosx)
    {
        double sina = sine[pos], cosa = cosi[pos];
        sine[pos] = sina * cosx + cosa * sinx;
        cosi[pos] = cosa * cosx - sina * sinx;
    }

    inline void pushdown(int pos)
    {
        if (!tag[pos])
            return;
        double sinx = sin(tag[pos]), cosx = cos(tag[pos]);
        update(ls, sinx, cosx);
        update(rs, sinx, cosx);
        tag[ls] += tag[pos];
        tag[rs] += tag[pos];
        tag[pos] = 0;
    }

    void build(int l, int r, int pos)
    {
        if (l == r)
        {
            sine[pos] = sin(a[l]);
            cosi[pos] = cos(a[l]);
            return;
        }
        build(l, mid, ls);
        build(mid + 1, r, rs);
        pushup(pos);
    }

    void modify(int nl, int nr, int l, int r, int pos, int k)
    {
        if (nl <= l && r <= nr)
        {
            update(pos, sink, cosk);
            tag[pos] += k;
            return;
        }
        pushdown(pos);
        if (nl <= mid)
            modify(nl, nr, l, mid, ls, k);
        if (nr > mid)
            modify(nl, nr, mid + 1, r, rs, k);
        pushup(pos);
    }

    double query(int nl, int nr, int l, int r, int pos)
    {
        if (nl <= l && r <= nr)
            return sine[pos];
        double res = 0;
        pushdown(pos);
        if (nl <= mid)
            res += query(nl, nr, l, mid, ls);
        if (nr > mid)
            res += query(nl, nr, mid + 1, r, rs);
        return res;
    }
} T;