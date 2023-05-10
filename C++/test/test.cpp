#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 这是一个贪心算法问题。我们需要在限定的时间内完成尽可能多的游戏任务，以获得尽可能多的奖金。在这个问题中，我们关注的是游戏任务的截止日期和未能在规定期限内完成时的罚款。

// 首先，我们创建一个名为 `Game` 的结构体，用于存储每个游戏任务的截止日期（deadline）和罚款金额（penalty）。接着，我们定义一个比较函数 `compare`，用于按照罚款金额从大到小对游戏任务进行排序。

//`getMaxMoney` 函数是整个算法的核心。我们首先对游戏任务进行排序，然后创建一个名为 `slots` 的布尔向量，用于表示每个时间段是否已被占用。
// 接着，我们遍历排序后的游戏任务。对于每个游戏任务，我们尝试从其截止日期开始向前查找未被占用的时间段。
// 如果我们找到了未被占用的时间段，就将其标记为已占用。否则，我们将需要支付的罚款金额从奖金中扣除。

// 最后，在 `main` 函数中，我们读取输入并调用 `getMaxMoney` 函数来计算小伟可以赢得的最多奖金。

struct Game
{
    int deadline;
    int penalty;
};

bool compare(Game a, Game b)
{
    return a.penalty > b.penalty;
}

int getMaxMoney(int m, int n, vector<Game> &games)
{
    sort(games.begin(), games.end(), compare);
    vector<bool> slots(n + 1, false);

    int totalMoney = m;
    for (int i = 0; i < n; ++i)
    {
        int j;
        for (j = games[i].deadline; j > 0; --j)
        {
            if (!slots[j])
            {
                slots[j] = true;
                break;
            }
        }
        if (j == 0)
        {
            totalMoney -= games[i].penalty;
        }
    }
    return totalMoney;
}

int main()
{
    int m, n;
    while (cin >> m >> n)
    {
        vector<Game> games(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> games[i].deadline;
        }
        for (int i = 0; i < n; ++i)
        {
            cin >> games[i].penalty;
        }

        cout << getMaxMoney(m, n, games) << endl;
    }
    return 0;
}
