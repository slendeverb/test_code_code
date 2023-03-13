#include <iostream>
using namespace std;

int A(int n, int m)
{
    int res = 1;
    for (int i = m; i >= 1; i--)
    {
        res *= n; // n × n-1 × n-2 × ... n-m，m就是需要减1的次数
        n--;
    }
}

int C(int n, int m)
{
    int up = 1;   // 分子
    int down = 1; // 分母
    m = min(m, n - m);

    for (int i = m; i >= 1; i--)
    {
        up *= n; // 累乘得到分子
        n--;
        down *= i; // 累乘得到分母
    }
    return up / down;
}
