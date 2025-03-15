// 倍增算法，顾名思义，就是不断地翻倍。
// 虽然是一种基础算法，但它能够使得线性的处理转化为对数级的处理，大大地优化时间复杂度，在很多算法中都有应用，
// 其中最常见的就是ST表以及LCA（树上最近公共祖先）了。

// 引例一
// 在你面前的桌子上，摆着无数个重量为任意整数的胡萝卜；
// 接着告诉你一个数字 n，问你要怎么挑选，使得你选出的胡萝卜能够表示出[1,n]区间内的所有整数重量？
// 读完题后我们马上就能想到一种选法，那就是选 n 个重量为1的胡萝卜，这样就能通过加减表示出[1,n]内的所有重量了
// 但问题是......这样挑选的胡萝卜是不是太多了点?
// 我们很快就能发现，只需要选择重量为 1,2,4,8,16 的胡萝卜，就能表示[1,31]内的所有重量......
// 只需要选择重量 1,2,4...2^i的胡萝下，就能表示[1,2^(i+1) -1]内的所有重量。
// 也就是说，对于给定的数字n，根本不需要选那么多胡萝卜，只需要 [log_2(n)] ([]为向下取整)个胡萝卜就够啦!
// 由此引例我们得出一个结论: 只需要 log_2(n) 的预处理，就能表示出 [1,n] 区间内的所有情况

// 引例二
// 有一个环状的操场，操场被分割为 [1,n] 个小块，每个小块上写着一个数字
// 有一只小白兔站在操场的起点，它每次可以跳 k 个小块，然后拿走等同于它所站小块上数字数量的胡萝卜，问它跳 m 次，总共可以拿到几个胡萝卜?
// 如果能够算出来的话，小白兔就能把所有的胡萝卜都带回家吃啦!
// 注: 1<k<n<10^6,1<m<10^18
// 同样的，读完题我们马上就能想到最简单暴力的方法:那就是让小白兔一次一次跳，每次跳都把答案加上去，直到跳完 m 次。
// 可是... m 最大可以达到 10^18 哎，小白兔就算跳到累死，恐怕也吃不到一根胡萝卜。
// 这时候我们想起了从引例一得出的结论:
// 只需要记录跳 1,2,4,8,16...2^([log_2(m)]) 次分别能够拿到的胡萝卜数，就能得到跳[1,m]区间内任何一个数字能拿到的胡萝卜数
// 这样子，即便 m=10^18，也只需要预处理64以内的数据就可以了
// 时间复杂度从 O(m)变成了 O(nlog_2(m)) (因为每个小块都需要处理)
// 询问的时间复杂度则是 O(log_2(m))，因为需要遍历其二进制的每一位

// 接下来介绍处理方案:
// 我们设 to[x][i]代表从起点x跳2^i步后到达的小块编号，carrot[x][i] 表示从起点x跳2^i步后能拿到的胡萝卜总数。
// 则有式子to[x][i] = to[to[x][i-1]][i-1]。即跳2^i步相当于先跳 2^(i-1) 步再跳 2^(i-1) 步
// carrot[x][i] = carrot[x][i - 1] + carrot[to[x][i-1]][i-1]
// 写成代码如下:
// 为了好处理，我们设区间为左闭右开，即不计入终点的胡萝数
#include <iostream>
using namespace std;

const int MAXN = 1e6 + 5;
long long to[MAXN][65], carrot[MAXN][65];
long long num[MAXN];
long long n, m, k;

int main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
    }
    for (int x = 1; x <= n; x++)
        to[x][0] = (x + k) % n + 1, carrot[x][0] = num[x];
    for (int i = 1; i <= 64; i++)
        for (int x = 1; x <= n; x++)
        {
            to[x][i] = to[to[x][i - 1]][i - 1];
            carrot[x][i] = carrot[x][i - 1] + carrot[to[x][i - 1]][i - 1];
        }
    int p = 0, now = 1, ans = 0;
    while (m)
    { // 若m的二进制第p-1位为1，则答案加上去
        if (m & (1ll << p))
            ans += carrot[now][p], now = to[now][p];
        m ^= (1 << p); // 第p-1位清空
        p++;
    }
    return 0;
}