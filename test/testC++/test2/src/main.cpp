#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

const int VEX_NUM = 20;
const int EDGE_NUM = 49;

bool same(int i, auto& compartment, const auto& graph) {
    for (int j = 1; j <= VEX_NUM; j++) {
        if (graph[i][j] == 1 && compartment[i] == compartment[j]) {
            return false;
        }
    }
    return true;
}

bool dfs(int i, const int m, auto& compartment, const auto& graph) {
    if (i > VEX_NUM) {
        return true;
    }
    for (int j = 1; j <= m; j++) {
        compartment[i] = j;
        if (same(i, compartment, graph)) {
            return dfs(i + 1, m, compartment, graph);
        }
        compartment[i] = 0;
    }
    return false;
}

void solve() {
    std::ifstream in{"../../../in.txt"};
    std::ofstream out{"../../../out.txt"};
    std::vector<std::vector<int>> graph(VEX_NUM + 1, std::vector<int>(VEX_NUM + 1, 0));
    int x, y;
    for (int i = 1; i <= EDGE_NUM; i++) {
        in >> x >> y;
        graph[x][y] = 1;
        graph[y][x] = 1;
    }
    in.close();

    std::vector<int> compartment(VEX_NUM + 1, 0);
    for (int m = 1;; m++) {
        std::fill(std::begin(compartment), std::end(compartment), 0);
        if (dfs(1, m, compartment, graph)) {
            out << std::format("所有化学试剂最少需要 {} 个隔间存储\n", m);
            std::vector<std::set<int>> ans(m, std::set<int>());
            for (int i = 1; i <= VEX_NUM; i++) {
                ans[compartment[i] - 1].insert(i);
            }
            for (int i = 0; i < m; i++) {
                out << std::format("隔间 {} 存储的化学试剂编号: ", i + 1);
                for (const auto& x : ans[i]) {
                    out << x << " ";
                }
                out << "\n";
            }
            return;
        }
    }
    out.close();
}

int main() {
    solve();
    return 0;
}