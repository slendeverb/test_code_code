#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> soldiers;
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        soldiers.push_back(std::make_pair(x, y));
    }

    // 按照 x 坐标进行排序
    std::sort(soldiers.begin(), soldiers.end());

    // 找到 y 坐标的中位数
    int y_median = soldiers[n / 2].second;

    // 计算 x 坐标需要移动的步数
    int x_median = soldiers[n / 2].first;
    int min_x_steps = 0;
    for (const auto& soldier : soldiers) {
        min_x_steps += std::abs(soldier.first - x_median);
    }

    // 计算 y 坐标需要移动的步数
    int min_y_steps = 0;
    for (const auto& soldier : soldiers) {
        min_y_steps += std::abs(soldier.second - y_median);
    }

    // 计算总的最少移动步数
    int min_steps = min_x_steps + min_y_steps;

    std::cout << min_steps << std::endl;

    return 0;
}
