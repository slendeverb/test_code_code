#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 1e6 + 10;
typedef long long ll;

struct Segment_tree
{
    ll sum, add;
    int l, r;
} s[MAXN << 2];

int n, m, a[MAXN];

void update(int pos)
{
    s[pos].sum = (s[pos << 1].sum + s[pos << 1 | 1].sum);
    return;
}

void build_tree(int pos, int l, int r)
{
    s[pos].l = l;
    s[pos].r = r;
    if (l == r)
    {
        s[pos].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build_tree(pos << 1, l, mid);
    build_tree(pos << 1 | 1, mid + 1, r);
    update(pos);
    return;
}

void pushdown(int pos)
{
    s[pos << 1].sum = s[pos << 1].sum + s[pos].add * (s[pos << 1].r - s[pos << 1].l + 1);
    s[pos << 1 | 1].sum = s[pos << 1 | 1].sum + s[pos].add * (s[pos << 1 | 1].r - s[pos << 1 | 1].l + 1);

    s[pos << 1].add = s[pos << 1].add + s[pos].add;
    s[pos << 1 | 1].add = s[pos << 1 | 1].add + s[pos].add;

    s[pos].add = 0;
    return;
}

void ChangeAdd(int pos, int x, int y, int k)
{
    if (x <= s[pos].l && s[pos].r <= y)
    {
        s[pos].add = s[pos].add + k;
        s[pos].sum = s[pos].sum + k * (s[pos].r - s[pos].l + 1);
        return;
    }
    pushdown(pos);
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
    {
        ChangeAdd(pos << 1, x, y, k);
    }
    if (y > mid)
    {
        ChangeAdd(pos << 1 | 1, x, y, k);
    }
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
    ll ret = 0;
    int mid = (s[pos].l + s[pos].r) >> 1;
    if (x <= mid)
    {
        ret = ret + AskRange(pos << 1, x, y);
    }
    if (y > mid)
    {
        ret = ret + AskRange(pos << 1 | 1, x, y);
    }
    return ret;
}

int main()
{
    // ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    build_tree(1, 1, n);
    int operate, x, y, k;
    while (m--)
    {
        cin >> operate;
        if (operate == 1)
        {
            cin >> x >> y >> k;
            ChangeAdd(1, x, y, k);
        }
        else if (operate == 2)
        {
            cin >> x >> y;
            cout << AskRange(1, x, y) << "\n";
        }
    }
    return 0;
}