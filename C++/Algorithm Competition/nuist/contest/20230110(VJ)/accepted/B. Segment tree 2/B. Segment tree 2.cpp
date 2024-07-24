#include <iostream>
#include <cstdio>
using namespace std;

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

void update(int pos)
{
    s[pos].sum = (s[pos << 1].sum + s[pos << 1 | 1].sum) % mod;
    return;
}

void pushdown(int pos)
{
    s[pos << 1].sum = (s[pos << 1].sum * s[pos].mul + s[pos].add * (s[pos << 1].r - s[pos << 1].l + 1)) % mod;
    s[pos << 1 | 1].sum = (s[pos << 1 | 1].sum * s[pos].mul + s[pos].add * (s[pos << 1 | 1].r - s[pos << 1 | 1].l + 1)) % mod;

    s[pos << 1].mul = (s[pos << 1].mul * s[pos].mul) % mod;
    s[pos << 1 | 1].mul = (s[pos << 1 | 1].mul * s[pos].mul) % mod;

    s[pos << 1].add = (s[pos << 1].add * s[pos].mul + s[pos].add) % mod;
    s[pos << 1 | 1].add = (s[pos << 1 | 1].add * s[pos].mul + s[pos].add) % mod;

    s[pos].add = 0;
    s[pos].mul = 1;
    return;
}

void build_tree(int pos, int l, int r)
{
    s[pos].l = l;
    s[pos].r = r;
    s[pos].mul = 1;

    if (l == r)
    {
        s[pos].sum = a[l] % mod;
        return;
    }

    int mid = (l + r) >> 1;
    build_tree(pos << 1, l, mid);
    build_tree(pos << 1 | 1, mid + 1, r);
    update(pos);
    return;
}

void ChangeMul(int pos, int x, int y, int k)
{
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
        ChangeMul(pos << 1, x, y, k);
    if (y > mid)
        ChangeMul(pos << 1 | 1, x, y, k);
    update(pos);
    return;
}

void ChangeAdd(int pos, int x, int y, int k)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        s[pos].add = (s[pos].add + k) % mod;
        s[pos].sum = (s[pos].sum + k * (s[pos].r - s[pos].l + 1)) % mod;
        return;
    }

    pushdown(pos);
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        ChangeAdd(pos << 1, x, y, k);
    if (y > mid)
        ChangeAdd(pos << 1 | 1, x, y, k);
    update(pos);
    return;
}

ll AskRange(int pos, int x, int y)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        return s[pos].sum;
    }

    pushdown(pos);
    ll val = 0;
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
        val = (val + AskRange(pos << 1, x, y)) % mod;
    if (y > mid)
        val = (val + AskRange(pos << 1 | 1, x, y)) % mod;
    return val;
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m >> mod;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    build_tree(1, 1, n);
    while (m--)
    {
        int operate, x, y, k;
        cin >> operate;
        if (operate == 1)
        {
            cin >> x >> y >> k;
            ChangeMul(1, x, y, k);
        }
        else if (operate == 2)
        {
            cin >> x >> y >> k;
            ChangeAdd(1, x, y, k);
        }
        else if (operate == 3)
        {
            cin >> x >> y;
            cout << AskRange(1, x, y) << "\n";
        }
    }
    return 0;
}