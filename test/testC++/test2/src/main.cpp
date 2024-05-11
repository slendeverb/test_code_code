#include <iostream>
#include <vector>

void solve()
{
    const int num_days = 7;
    const int num_subjects = 4;
    std::vector<std::vector<int>> credits {
        { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 4, 4, 5, 8, 0, 0, 0 },
        { 0, 3, 5, 6, 7, 0, 0, 0 },
        { 0, 5, 6, 8, 8, 0, 0, 0 },
        { 0, 2, 4, 7, 8, 0, 0, 0 }
    };
    std::vector<std::vector<int>> dp(num_subjects + 2, std::vector<int>(num_days + 1, 0));
    std::vector<std::vector<int>> nxt(dp);

    for (int i = num_subjects; i >= 1; i--) {
        for (int s = 1; s <= num_days; s++) {
            int max_credits = 0;
            int max_j = 0;
            for (int j = 0; j <= s; j++) {
                if (credits[i][j] + dp[i + 1][s - j] >= max_credits) {
                    max_credits = credits[i][j] + dp[i + 1][s - j];
                    max_j = j;
                }
            }
            dp[i][s] = max_credits;
            nxt[i][s] = max_j;
        }
    }
    for (auto& x : dp) {
        for (auto& y : x) {
            std::cout << y << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    for (auto& x : nxt) {
        for (auto& y : x) {
            std::cout << y << " ";
        }
        std::cout << "\n";
    }
    std::cout << "最高总学分为: " << dp[1][num_days] << "\n";

    int allocate_days = nxt[1][num_days];
    int rest_days = num_days - allocate_days;
    for (int k = 1; k <= num_subjects; k++) {
        std::cout << "第" << k << "门课分配天数为: " << allocate_days << "\n";
        allocate_days = nxt[k + 1][rest_days];
        rest_days -= allocate_days;
    }
}

int main()
{
    solve();
    return 0;
}