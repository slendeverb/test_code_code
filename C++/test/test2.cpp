#include <iostream>
using namespace std;

#define ls (pos << 1)
#define rs (pos << 1 | 1)

typedef long long ll;

const int MAXN = 1e5 + 10;
int N, Q, l, r, x;
const int mod = 1e9 + 7;
int a[MAXN];
char c;

struct Segment_Tree
{
    ll sum, add, sum_square;
    int l, r;
} s[MAXN << 2];

void pushup(int pos)
{
    s[pos].sum = (s[ls].sum + s[rs].sum) % mod;
    s[pos].sum_square = (s[ls].sum_square + s[rs].sum_square) % mod;
    return;
}

void pushdown(int pos)
{
    s[ls].sum_square = (s[ls].sum_square + 2 * s[ls].sum * s[pos].add + s[pos].add * s[pos].add * (s[ls].r - s[ls].l + 1)) % mod;
    s[rs].sum_square = (s[rs].sum_square + 2 * s[rs].sum * s[pos].add + s[pos].add * s[pos].add * (s[rs].r - s[rs].l + 1)) % mod;

    s[ls].sum = (s[ls].sum + s[pos].add * (s[ls].r - s[ls].l + 1)) % mod;
    s[rs].sum = (s[rs].sum + s[pos].add * (s[rs].r - s[rs].l + 1)) % mod;

    s[ls].add = (s[ls].add + s[pos].add) % mod;
    s[rs].add = (s[rs].add + s[pos].add) % mod;

    s[pos].add = 0;
    return;
}

void build_tree(int pos, int l, int r)
{
    s[pos].l = l;
    s[pos].r = r;

    if (l == r)
    {
        s[pos].sum = a[l] % mod;
        s[pos].sum_square = (a[l] * a[l]) % mod;
        return;
    }

    int mid = (l + r) >> 1;
    build_tree(ls, l, mid);
    build_tree(rs, mid + 1, r);

    pushup(pos);
    return;
}

void ChangeAdd(int pos, int x, int y, int k)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        s[pos].add = (s[pos].add + k) % mod;
        s[pos].sum_square = (s[pos].sum_square + 2 * s[pos].sum * s[pos].add + s[pos].add * s[pos].add * (s[pos].r - s[pos].l + 1)) % mod;
        s[pos].sum = (s[pos].sum + k * (s[pos].r - s[pos].l + 1)) % mod;
        return;
    }

    pushdown(pos);
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
    {
        ChangeAdd(ls, x, y, k);
    }
    if (y > mid)
    {
        ChangeAdd(rs, x, y, k);
    }
    pushup(pos);
    return;
}

ll query(int pos, int x, int y)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        return s[pos].sum_square;
    }
    pushdown(pos);
    ll val = 0;
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
    {
        val = (val + query(ls, x, y)) % mod;
    }
    if (y > mid)
    {
        val = (val + query(rs, x, y)) % mod;
    }
    return val;
}

int main()
{
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
    {
        cin >> a[i];
    }
    build_tree(1, 1, N);
    while (Q--)
    {
        cin >> c;
        if (c == 'u')
        {
            cin >> l >> r >> x;
            ChangeAdd(1, l, r, x);
        }
        if (c == 'q')
        {
            cin >> l >> r;
            ll ans = query(1, l, r);
            cout << ans << "\n";
        }
    }
    return 0;
}