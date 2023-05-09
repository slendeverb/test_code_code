#include <bits/stdc++.h>
using namespace std;
int a, b, len, last[1005], ans[1005];
struct F
{
    int a, b;
    F(int c, int d)
    {
        int l = __gcd(c, d);
        a = c / l, b = d / l;
    }
    F() { a = 0, b = 1; }
    bool operator==(const F &t) const { return a * t.b == b * t.a; }
    bool operator<(const F &t) const { return a * t.b < b * t.a; }
    bool operator>(const F &t) const { return !(*this < t) && !(*this == t); }
    bool operator!=(const F &t) const { return !(*this == t); }
    bool operator<=(const F &t) const { return !(*this > t); }
    bool operator>=(const F &t) const { return !(*this < t); }
    F operator-(const F &t) const
    {
        int x = a * t.b - t.a * b, y = b * t.b;
        int l = __gcd(x, y);
        return F(x / l, y / l);
    }
    F operator+(const F &t) const
    {
        int x = a * t.b + t.a * b, y = b * t.b;
        int l = __gcd(x, y);
        return F(x / l, y / l);
    }
    F operator*(const F &t) const
    {
        int x = a * t.a, y = b * t.b, l = __gcd(x, y);
        return F(x / l, y / l);
    }
} x; // 用结构体存储分数（避免精度误差）
void dfs(int a, F b, int c, int las)
{
    if (b > x || c > a)
        return; // 出界了
    if (c == a)
    { // ↓是单位分数、↓在10^-7以内、↓满足递增
        if ((x - b).a == 1 && (x - b).b <= 1e7 && (x - b).b > las)
        {
            if ((x - b).b < ans[len])
            {
                // 比当前最优解优
                for (int i = 1; i <= len; i++)
                {
                    ans[i] = last[i];
                }
                ans[len] = (x - b).b; // 更新答案
            }
        }
        return;
    }
    for (int i = las + 1; i <= ans[len]; i++)
    { // ans[len]是目前的“最优解”如果没有它优，就不用继续枚举了
        if (F(a - c + 1, i) < (x - b))
            return;
        last[c] = i;
        dfs(a, b + F(1, i), c + 1, i);
    }
}
int main()
{
    scanf("%d%d", &a, &b);
    x = F(a, b);
    while (1)
    {
        ans[++len] = INT_MAX; // 初始为极大值
        dfs(len, F(0, 1), 1, 0);
        if (ans[len] != INT_MAX)
        { // 有解了
            for (int i = 1; i <= len; i++)
                printf("%d ", ans[i]); // 输出
            break;
        }
    }
    return 0;
}