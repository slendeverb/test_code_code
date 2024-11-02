#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

struct Node {
    int size{0};
    int start_address{0};
    bool free_state{true};
    static inline const int min_size{1};

    auto operator<=>(const Node& a) const { return size <=> a.size; }
};

void bestFit(std::vector<Node>& free_nodes, const std::vector<int>& tasks) {
    for (int i = 0; i < tasks.size(); i++) {
        std::cout << "任务" << i + 1 << "需要的内存为: " << tasks[i] << "K\n";
        std::sort(free_nodes.begin(), free_nodes.end(), std::less<>{});
        int alloc_size = 0;
        for (int j = 0; j < free_nodes.size(); j++) {
            if (!free_nodes[j].size) {
                continue;
            }
            if (free_nodes[j].size >= tasks[i]) {
                free_nodes[j].size -= tasks[i];
                free_nodes[j].start_address += tasks[i];
                alloc_size += tasks[i];
                if (free_nodes[j].size < Node::min_size) {
                    alloc_size += free_nodes[j].size;
                    free_nodes[j].size = 0;
                }
                free_nodes[j].free_state = false;
                break;
            }
        }
        std::cout << "给任务" << i + 1 << "分配了" << alloc_size << "K内存\n\n";
    }
}

int main(int argc, char** argv) {
    std::vector<Node> free_nodes{{12, 20},   {32, 32},   {64, 64},    {128, 128},
                                     {256, 256}, {512, 512}, {1024, 1024}};

    std::vector<int> tasks{2, 2, 3, 3, 4, 4, 5, 7, 8, 10, 16, 20, 32, 64, 128, 256, 1024};
    std::shuffle(tasks.begin(), tasks.end(), std::mt19937_64{std::random_device{}()});
    bestFit(free_nodes, tasks);
}