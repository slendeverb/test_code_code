#include "header.h"

class Solution {
   public:
    int countSpecialNumbers(int n) {
        std::string s = std::to_string(n);
        auto dp = [f = [&s](auto&& self, int i, int mask, bool is_limit, bool is_num) -> int {
            if (i == s.size()) {
                return is_num;
            }
            int res = 0;
            if (!is_num) {
                res = self(self, i + 1, mask, false, false);
            }
            int up = is_limit ? s[i] - '0' : 9;
            for (int d = (1 - is_num); d <= up; d++) {
                if (((mask >> d) & 1) == 0) {
                    res += self(self, i + 1, mask | (1 << d), is_limit && d == up, true);
                }
            }
            return res;
        }](int i, int mask, bool is_limit, bool is_num) { return f(f, i, mask, is_limit, is_num); };
        return dp(0, 0, true, false);
    }
};

int main(int argc, char** argv) {
    int n = 135;
    std::cout << std::format("{}\n", Solution{}.countSpecialNumbers(n));
}