#include <algorithm>
#include <execution>
#include <format>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int MACHINE_NUM = 600;

struct Task {
    int idx;
    size_t t;
    int machine_No;

    Task() = default;
    Task(int idx, size_t t) : idx{idx}, t{t} {}

    decltype(auto) operator<=>(const Task& a) const { return t <=> a.t; }
};

void solve() {
    std::string input_path{"../../../in.txt"};
    std::ifstream in{input_path};
    std::string output_path{"../../../out.txt"};
    std::ofstream out{output_path};
    int idx;
    size_t t;
    std::vector<Task> tasks;
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> pq;
    while (in >> idx >> t) {
        tasks.emplace_back(idx, t);
    }
    if (std::size(tasks) <= MACHINE_NUM) {
        out << std::format(
            "多机调度方案: \n"
            "  为每一个作业分配一台机器\n"
            "所有作业最短在时间 {} 内能完成\n",
            std::max_element(std::execution::par_unseq, std::begin(tasks), std::end(tasks))
                .base()
                ->t);
        return;
    }
    std::sort(std::begin(tasks), std::end(tasks), std::greater{});
    out << std::format("多机调度方案: \n");
    for (int i = 0; i < MACHINE_NUM; i++) {
        tasks[i].machine_No = i + 1;
        out << std::format("  给机器 {0} 分配作业 {1}, 执行时间为 {2}, 占用时间段 [{3}, {4}]\n",
                           tasks[i].machine_No, tasks[i].idx, tasks[i].t, 0, tasks[i].t);
        pq.push(tasks[i]);
    }
    size_t max_time = 0;
    for (int i = MACHINE_NUM; i < std::size(tasks); i++) {
        auto element = pq.top();
        pq.pop();
        out << std::format("  给机器 {0} 分配作业 {1}, 执行时间为 {2}, 占用时间段 [{3}, {4}]\n",
                           element.machine_No, tasks[i].idx, tasks[i].t, element.t,
                           element.t + tasks[i].t);
        element.t += tasks[i].t;
        max_time = std::max(max_time, element.t);
        pq.push(element);
    }
    out << std::format("所有作业最短在时间 {} 内能完成\n", max_time);
    in.close();
    out.close();
}

int main() {
    solve();
    return 0;
}