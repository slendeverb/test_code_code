#include <iostream>
using namespace std;

int n, m;
const int N = 1e6 + 10;
int a[N], tree[N << 2];

void pushup(int pos)
{
    tree[pos] = max(tree[pos << 1], tree[pos << 1 | 1]);
}

void build(int pos, int l, int r)
{
    if (l == r)
    {
        tree[pos] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(pos << 1, l, mid);
    build(pos << 1 | 1, mid + 1, r);
    pushup(pos);
}

void change(int pos, int l, int r, int x, int y)
{
    if (l == r)
    {
        if (tree[pos] < y)
            tree[pos] = y;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        change(pos << 1, l, mid, x, y);
    else
        change(pos << 1 | 1, mid + 1, r, x, y);
    pushup(pos);
}

int query(int pos, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[pos];
    int mid = (l + r) >> 1, ans = -1e9;
    if (x <= mid)
        ans = max(ans, query(pos << 1, l, mid, x, y));
    if (y > mid)
        ans = max(ans, query(pos << 1 | 1, mid + 1, r, x, y));
    return ans;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    build(1, 1, n);
    while (m--)
    {
        char ch;
        int x, y;
        cin >> ch >> x >> y;
        if (ch == 'Q')
        {
            cout << query(1, 1, n, x, y) << "\n";
        }
        if (ch == 'U')
        {
            change(1, 1, n, x, y);
        }
    }
    return 0;
}