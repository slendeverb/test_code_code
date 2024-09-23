#include "header.h"

class Solution {
   public:
    int maxScoreSightseeingPair(std::vector<int>& values) {
        int ans = 0;
        int mx = values[0];
        for (int j = 1; j < values.size(); j++) {
            ans = std::max(ans, mx + values[j] - j);
            mx = std::max(mx, values[j] + j);
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> values;
    std::ifstream input{"../../../in.txt"};
    std::string s;
    while (!std::getline(input, s, ',').eof()) {
        values.push_back(std::stoi(s));
    }
    auto start = std::chrono::steady_clock::now();
    auto ans = Solution{}.maxScoreSightseeingPair(values);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_seconds = std::chrono::duration<int64_t, std::nano>(end - start);
    std::println("ans: {}, time: {}", ans, elapsed_seconds);
}