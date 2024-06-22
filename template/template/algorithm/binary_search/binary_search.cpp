#include <iostream>
using namespace std;

int a[1000005];
int n, m;

bool check(int k)
{ // 检查可行性，k 为锯片高度
    long long sum = 0;
    for (int i = 1; i <= n; i++)          // 检查每一棵树
        if (a[i] > k)                     // 如果树高于锯片高度
            sum += (long long)(a[i] - k); // 累加树木长度
    return sum >= m;                      // 如果满足最少长度代表可行
}

int find()
{
    int l = 1, r = 1e9; // 二分区间为[l,mid-1] [mid,r]
    while (l < r)
    {                               // 如果两点不相邻
        int mid = (l + r + 1) >> 1; // 取中间值
        if (check(mid))             // 如果可行
            l = mid;                // 升高锯片高度
        else
            r = mid - 1; // 否则降低锯片高度
    }
    return l; // 返回左边值
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cout << find();
    return 0;
}

//

long long solve()
{
    long long l = 1, r = n, mid, ans;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
        return mid;
    }
}