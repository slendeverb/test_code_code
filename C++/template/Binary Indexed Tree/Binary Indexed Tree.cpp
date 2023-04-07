#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6 + 10;
int n, a[N], c[N]; // 对应原数组和树状数组

int lowbit(int x)
{
    return x & (-x);
}

void update(int i, int k) // 在i位置加上k
{
    while (i <= n)
    {
        c[i] += k;
        i += lowbit(i);
    }
}

int getsum(int i) // 求A[1 ~ i]的和
{
    int res = 0;
    while (i > 0)
    {
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}

void update(int x) // 单点修改最大值
{
    int lx, i;
    while (x <= n)
    {
        c[x] = a[x];
        lx = lowbit(x);
        for (i = 1; i < lx; i <<= 1)
            c[x] = max(c[x], c[x - i]);
        x += lowbit(x);
    }
}

int getmax(int x, int y) // 求区间[x,y]的最大值
{
    int ans = 0;
    while (y >= x)
    {
        ans = max(a[y], ans);
        y--;
        for (; y - lowbit(y) >= x; y -= lowbit(y))
            ans = max(c[y], ans);
    }
    return ans;
}


// 上升子序列
int cnt, b[N], Left[N], Right[N];

void add(int x, int val)
{
    while (x <= N)
    {
        c[x] += val;
        x += lowbit(x);
    }
}
int query(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
int Q(int val)
{
    // Q的作用是对于val,返回它的离散化值，即为val在离散化数组中的下标
    // lower_bound为二分查找val,返回其地址
    return lower_bound(b + 1, b + 1 + cnt, val) - b;
}
int main()
{
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    cnt = unique(b + 1, b + 1 + n) - (b + 1); // unique返回去重后数组末尾地址的下一位，所以要减(b+1)，m为去重后数组长度
    for (int i = 1; i <= n; i++)
    {
        add(Q(a[i]), 1);
        Left[i] = query(Q(a[i]) - 1);
    }
    memset(c, 0, sizeof(c));
    for (int i = n; i >= 1; i--)
    {
        add(Q(a[i]), 1);
        Right[i] = n - i + 1 - query(Q(a[i]));
    }
    int ans = 0;
    for (int i = 2; i < n; i++)
    {
        ans += Left[i] * Right[i];
    }
}