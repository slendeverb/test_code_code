// #include "header.h"
#include <bits/stdc++.h>

class Solution {
   public:
    int minSpeedOnTime(std::vector<int>& dist, double hour) {
        int n = dist.size();
        long long l = 0, r = INT_MAX;
        int ans = -1;
        auto check = [&](long long mid) -> bool {
            double sum = 0;
            for (int i = 0; i < n - 1; i++) {
                sum += ceil((double)dist[i] / mid);
            }
            sum += (double)dist[n - 1] / mid;
            return fabs(sum - hour) < 1e-12 || sum < hour;
        };
        while (l <= r) {
            long long mid = ((r - l) >> 1) + l;
            if (check(mid)) {
                r = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

int main(int argc, char** argv) {
    std::vector<int> dist{1,1,100000};
    double hour = 2.01;
    std::cout << Solution{}.minSpeedOnTime(dist, hour) << "\n";
}