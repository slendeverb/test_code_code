// #include "header.h"
#include <bits/stdc++.h>

class Solution {
   public:
    long long minimumTime(std::vector<int>& time, int totalTrips) {
        auto check = [&](long long x) -> bool {
            long long sum = 0;
            for (int t : time) {
                sum += x / t;
                if (sum >= totalTrips) {
                    return true;
                }
            }
            return false;
        };
        auto [min_time, max_time] = std::ranges::minmax(time);
        long long avg = (totalTrips - 1) / time.size() + 1;
        long long left = (long long)min_time * avg - 1;
        long long right = std::min((long long)max_time * avg, (long long)min_time * totalTrips);
        while (left + 1 < right) {
            long long mid = ((right - left) >> 1) + left;
            (check(mid) ? right : left) = mid;
        }
        return right;
    }
};

int main(int argc, char** argv) {
    std::vector<int> time{10000};
    int totalTrips{10000000};
    std::cout << std::format("{}\n", Solution{}.minimumTime(time, totalTrips));
}