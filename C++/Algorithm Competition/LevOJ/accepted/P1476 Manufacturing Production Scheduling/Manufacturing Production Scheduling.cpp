#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 我们总是想要让在A工厂加工时间少而在B工厂加工时间多的订单先生产

// 这类问题有一个固定的解法，即约翰逊（Johnson）算法，
// 约翰逊算法的思路是这样的，先进性分组，将at[i]<bt[i]，即在A工厂生产时间小于在B工厂生产时间的订单分为一组，记为M组，
// 而at[i]>=bt[i]，即在A工厂生产的时间大于等于在B工厂生产的时间的订单分成一组，记为N组，
// 对于M组中的订单我们将其按照在A工厂生产的时间的长短进行升序排序，
// 对于N组的订单我们将其按照在B工厂生产的时间的长短进行降序排序，
// 最后订单的生产顺序就是，先生产M组中的第一个订单，再生产N组中的第一个订单，再生产M组中的第二个订单，再生产N足中的第二个订单，
// 这样按照排序顺序，交替生产两组中的订单，此时生产顺序就是使得生产总时间最短的最优生产顺序

// 接下来，我们使用自定义的 compare 函数对产品进行排序。这个函数比较两个产品之间的 A 车间和 B 车间加工时间差。
// 这样排序后，我们可以确保在 A 车间加工时间较长的产品尽早开始加工，以便最大限度地减少总加工时间。

#define int long long

struct Product
{
    int id;
    int time_A;
    int time_B;
};

bool compare(const Product &a, const Product &b)
{
    if (a.time_A < a.time_B && b.time_A < b.time_B)
    {
        return a.time_A < b.time_A;
    }
    else if (a.time_A > a.time_B && b.time_A > b.time_B)
    {
        return a.time_B > b.time_B;
    }
    else
    {
        return a.time_A - a.time_B < b.time_A - b.time_B;
    }
}

signed main()
{
    int n;
    while (cin >> n)
    {
        vector<Product> products(n);
        for (int i = 0; i < n; ++i)
        {
            products[i].id = i;
            cin >> products[i].time_A;
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> products[i].time_B;
        }

        sort(products.begin(), products.end(), compare);

        int time_A_sum = 0;
        int time_B_sum = 0;
        for (const auto &product : products)
        {
            time_A_sum += product.time_A;
            time_B_sum = max(time_A_sum, time_B_sum) + product.time_B;
        }

        cout << time_B_sum << "\n";
    }

    return 0;
}
