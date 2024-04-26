#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void solve() {
    std::string input_path{"../../../in.txt"};
    std::ifstream in{input_path};
    std::string a, b;
    in >> a >> b;
    std::vector<size_t> dp(a.size() + 1, std::vector<size_t>(b.size() + 1, 0));
    for (size_t i = 0; i <= a.size(); i++) {
        dp[i][0] = 0;
    }
    for (size_t j = 0; j <= b.size(); j++) {
        dp[0][j] = 0;
    }
    for (size_t i = 1; i <= a.size(); i++) {
        for (size_t j = 1; j <= b.size(); j++) {
            if (a[i - 1] != b[j - 1]) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            } else {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
        }
    }
    size_t LCS_length = dp[a.size()][b.size()];
    std::string LCS_ans;
    for (size_t i = a.size(); i >= 1;) {
        for (size_t j = b.size(); j >= 1;) {
            if (dp[i][j] == dp[i][j - 1]) {
                j--;
            } else if (dp[i][j] == dp[i - 1][j]) {
                i--;
            } else {
                i--, j--;
                LCS_ans.push_back(a[i]);
            }
        }
    }
    std::cout << LCS_length << "\n"
              << std::string(LCS_ans.rbegin(), LCS_ans.rend()) << std::endl;
}

int main() {
    solve();
    return 0;
}