#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void solve() {
    std::string input_path{"../../../in.txt"};
    std::ifstream in{input_path};
    std::string a, b;
    in >> a >> b;
    size_t m = a.size(), n = b.size();
    std::vector<std::vector<size_t>> dp(m + 1, std::vector<size_t>(n + 1, 0));
    for (size_t i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }
    for (size_t j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }
    for (size_t i = 1; i <= m; i++) {
        for (size_t j = 1; j <= n; j++) {
            if (a[i - 1] != b[j - 1]) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            } else {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
        }
    }
    size_t LCS_length = dp[m][n];
    std::string LCS_ans;
    for (size_t i = m; i >= 1;) {
        for (size_t j = n; j >= 1;) {
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
    std::string output_path{"../../../out.txt"};
    std::ofstream out{output_path};
    out << LCS_length << "\n"
        << std::string(LCS_ans.rbegin(), LCS_ans.rend()) << std::endl;
}

int main() {
    solve();
    return 0;
}