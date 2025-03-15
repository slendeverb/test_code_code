#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define int long long
const int N = 1e5 + 10, mod = 1e9 + 7;
int a[N];
int n, q;
struct node
{
    int l, r;
    int sum;
    int copsum;
    int lazy;
} tr[N * 4];
void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    tr[u].sum %= mod;
    tr[u].copsum = tr[u << 1].copsum + tr[u << 1 | 1].copsum;
    tr[u].copsum %= mod;
}

void pushdown(int u)
{
    node &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.lazy)
    {
        left.sum += 2 * root.lazy % mod * left.copsum % mod;
        left.sum %= mod;
        left.sum += (left.r - left.l + 1) * root.lazy % mod * root.lazy % mod;
        left.sum %= mod;
        left.sum = (left.sum + mod) % mod;
        left.copsum += root.lazy % mod * (left.r - left.l + 1) % mod;
        left.copsum = (left.copsum + mod) % mod;
        left.lazy += root.lazy;
        left.lazy %= mod;

        right.sum += 2 * root.lazy % mod * right.copsum % mod;
        right.sum %= mod;
        right.sum += (right.r - right.l + 1) * root.lazy % mod * root.lazy % mod;
        right.sum %= mod;
        right.sum = (right.sum + mod) % mod;
        right.copsum += root.lazy % mod * (right.r - right.l + 1) % mod;

        right.copsum = (right.copsum + mod) % mod;
        right.lazy += root.lazy;
        right.lazy %= mod;
        root.lazy = 0;
    }
}
void build(int u, int l, int r)
{
    // printf("%lld %lld %lld\n",u,l,r);
    tr[u] = {l, r, 0, 0, 0};
    if (l == r)
    {
        tr[u].copsum = a[l];
        tr[u].sum = a[l] * a[l] % mod;
        tr[u].lazy = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}
int query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r)
        return tr[u].sum % mod;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    int sum = 0;
    if (l <= mid)
        sum += query(u << 1, l, r), sum %= mod;
    if (r > mid)
        sum += query(u << 1 | 1, l, r), sum %= mod;
    return sum % mod;
}
void modify(int u, int l, int r, int k)
{
    // printf("%lld %lld %lld\n",u,l,r);
    if (tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].lazy += k;
        tr[u].lazy %= mod;
        tr[u].sum += tr[u].copsum * k % mod * 2 % mod;
        tr[u].sum %= mod;
        tr[u].sum += (tr[u].r - tr[u].l + 1) % mod * k % mod * k % mod;
        tr[u].sum %= mod;
        tr[u].sum = (tr[u].sum + mod) % mod;
        tr[u].copsum += k * (tr[u].r - tr[u].l + 1) % mod;
        tr[u].copsum %= mod;
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid)
        modify(u << 1, l, r, k);
    if (r > mid)
        modify(u << 1 | 1, l, r, k);
    pushup(u);
    return;
}
signed main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    build(1, 1, n);
    for (int i = 1; i <= q; i++)
    {
        char op[2];
        scanf("%s", op);
        if (*op == 'u')
        {
            int l, r, k;
            scanf("%lld%lld%lld", &l, &r, &k);
            modify(1, l, r, k);
        }
        else
        {
            int l, r;
            scanf("%lld%lld", &l, &r);
            int ans = query(1, l, r);
            printf("%lld\n", (ans + mod) % mod);
        }
    }
    return 0;
}
