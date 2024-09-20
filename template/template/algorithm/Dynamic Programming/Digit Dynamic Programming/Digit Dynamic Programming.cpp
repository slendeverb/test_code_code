#include <bits/stdc++.h>

// v1.0 [0,n]
// leetcode 2376
class Solution {
   public:
    int countSpecialNumbers(int n) {
        std::string s = std::to_string(n);
        long long m = s.size();
        std::vector<std::vector<int>> memo(m, std::vector<int>(1 << 10, -1));
        auto dp = [f = [&](auto&& self, int i, int mask, bool is_limit, bool is_num) -> int {
            if (i == m) {
                return is_num;
            }
            if (!is_limit && is_num && memo[i][mask] != -1) {
                return memo[i][mask];
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
            if (!is_limit && is_num) {
                memo[i][mask] = res;
            }
            return res;
        }](int i, int mask, bool is_limit, bool is_num) { return f(f, i, mask, is_limit, is_num); };
        return dp(0, 0, true, false);
    }
};

// v2.0 [low,high]
// leetcode 2999
class Solution {
   public:
    // has no mask
    long long numberOfPowerfulInt(long long start, long long finish, int limit, std::string s) {
        std::string high = std::to_string(finish);
        long long n = high.size();
        std::string low = std::to_string(start);
        std::string zeros(n - low.size(), '0');
        low = zeros + low;
        long long diff = n - s.size();
        std::vector<long long> memo(n, -1);
        auto dp = [f = [&](auto&& self, long long i, bool limit_low, bool limit_high,
                           bool is_num) -> long long {
            if (i == n) {
                return is_num;
            }
            long long res = 0;
            if (!is_num && low[i] == '0') {
                if (i < diff) {
                    res = self(self, i + 1, true, false, false);
                }
            }
            if (!limit_low && !limit_high && memo[i] != -1) {
                return memo[i];
            }
            int lo = limit_low ? (low[i] - '0') : 0;
            int hi = limit_high ? (high[i] - '0') : 9;
            int d0 = is_num ? 0 : 1;
            if (i < diff) {
                for (int d = std::max(lo, d0); d <= std::min(hi, limit); d++) {
                    res += self(self, i + 1, limit_low && d == lo, limit_high && d == hi, true);
                }
            } else {
                int x = s[i - diff] - '0';
                if (x >= std::max(lo, d0) && x <= std::min(hi, limit)) {
                    res = self(self, i + 1, limit_low && x == lo, limit_high && x == hi, true);
                }
            }
            if (!limit_low && !limit_high) {
                memo[i] = res;
            }
            return res;
        }](long long i, bool limit_low, bool limit_high, bool is_num) {
            return f(f, i, limit_low, limit_high, is_num);
        };
        return dp(0, true, true, false);
    }

    // has mask, not activated
    long long numberOfPowerfulInt(long long start, long long finish, int limit, std::string s) {
        std::string high = std::to_string(finish);
        long long n = high.size();
        std::string low = std::to_string(start);
        std::string zeros(n - low.size(), '0');
        low = zeros + low;
        long long diff = n - s.size();
        std::vector<std::vector<long long>> memo(n, std::vector<long long>(1 << 10, -1));
        auto dp = [f = [&](auto&& self, long long i, long long mask, bool limit_low,
                           bool limit_high, bool is_num) -> long long {
            if (i == n) {
                return is_num;
            }
            long long res = 0;
            if (!is_num && low[i] == '0') {
                if (i < diff) {
                    res = self(self, i + 1, mask, true, false, false);
                }
            }
            if (!limit_low && !limit_high && memo[i][mask] != -1) {
                return memo[i][mask];
            }
            int lo = limit_low ? (low[i] - '0') : 0;
            int hi = limit_high ? (high[i] - '0') : 9;
            int d0 = is_num ? 0 : 1;
            if (i < diff) {
                for (int d = std::max(lo, d0); d <= std::min(hi, limit); d++) {
                    // if (((mask >> d) & 1) == 0)
                    res += self(self, i + 1, mask | (1 << d), limit_low && d == lo,
                                limit_high && d == hi, true);
                }
            } else {
                int x = s[i - diff] - '0';
                if (x >= std::max(lo, d0) && x <= std::min(hi, limit)) {
                    res = self(self, i + 1, mask | (1 << x), limit_low && x == lo,
                               limit_high && x == hi, true);
                }
            }
            if (!limit_low && !limit_high) {
                memo[i][mask] = res;
            }
            return res;
        }](long long i, long long mask, bool limit_low, bool limit_high, bool is_num) {
            return f(f, i, mask, limit_low, limit_high, is_num);
        };
        return dp(0, 0, true, true, false);
    }
};