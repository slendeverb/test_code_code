#include <iostream>
#include <cstring>
#include <algorithm>
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

/*
例如数组a[] = { 6 2 4 5 3 1 } 的逆序对的个数
可正向求，也可逆向求，思路是一样的
以正向思路：
数组a[i]出现的数字作为下标，使得数组c中该位置为1
a[0]=6，那就让c[6]=1
a[1]=2，让c[2]=1，此时数组c中元素为{0，1，0，0，0，1}，
（c中我们考虑下标从1开始，由于树状数组的特殊性，不使用下标0,因为0&(-0)=0，会一直在循环中）
那么c中下标为2的位置后面，标记1的位置都是a中比2大且出现比2早的，也就是出现在2前面的，那就能够同2构成逆序对
我们只要遍历到a中的当前元素k，然后对a维护的一个数组c求c[k]之后标记为1的个数，就是同k构成的逆序对的个数
而c中求区间中1的个数明显是动态求区间和，所以c维护成树状数组最方便。

而逆向的思路其实和正向差不多：
正向求逆序对，是遍历到a中的当前元素k，找之前遍历的比k大的数，构成逆序对，而c中比k大的数是否出现，
是在下标k之后标记。
当逆向求时，逆向遍历到a中的当前元素k，此时变成 找之前遍历的比k小的数 构成逆序对
而c中比k小的数是否出现，是在下标k之前标记，也就是求区间[1,k-1]出现1的个数。
*/

#include <iostream>
using namespace std;

// 正向求逆序对
int rsp(int a[], int N) // 数组a，大小N
{
    int sum = 0;
    // c是要维护的树状数组
    int *c = (int *)malloc(sizeof(int) * (N + 1));
    memset(c, 0, sizeof(int) * (N + 1));
    for (int i = 0; i < N; i++)
    {
        int k = a[i];
        // 维护c
        while (k <= N)
        {
            c[k] += 1;
            k += k & (-k);
        }
        // 求与当前a[i]构成的逆序对，也就求c中区间[k+1,N]的和
        // 树状数组区间求和一般是求[1,k]，所以我们转化一下，遍历到a[i]时c中有（i+1）个位置被标记为1,总和为（i+1）
        // 区间[k+1,N]的和 = (i+1) - 区间[1,k]的和
        k = a[i];
        int s = 0; // 区间[1,k]的和
        while (k > 0)
        {
            s += c[k];
            k -= k & (-k);
        }
        sum += (i + 1 - s); //(i+1 - s)就是当前与a[i]构成的逆序对的个数
    }
    return sum;
}

// 逆向求逆序对
int rsp_(int a[], int N)
{
    int sum = 0;
    int *c = (int *)malloc(sizeof(int) * (N + 1));
    memset(c, 0, sizeof(int) * (N + 1));
    for (int i = N - 1; i >= 0; i--)
    {
        int k = a[i];
        // 维护c
        while (k <= N)
        {
            c[k] += 1;
            k += k & (-k);
        }
        // 逆向求，找比a[i]小的，即求c中[1,k-1]的和
        k = a[i] - 1;
        while (k > 0)
        {
            sum += c[k];
            k -= k & (-k);
        }
    }
    return sum;
}
int main(void)
{
    int a[] = {6, 2, 4, 5, 3, 1};
    int ans1 = rsp(a, 6);
    cout << ans1 << endl;

    int ans2 = rsp_(a, 6);
    cout << ans2 << endl;
    // ans1为正向求的结果，ans2为逆向求的结果，两者是一样的，都是11
    system("pause");
    return 0;
}