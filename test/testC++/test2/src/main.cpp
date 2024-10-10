// #include "header.h"
#include <bits/stdc++.h>
using namespace std;

static const size_t N = 1e6 + 1;
std::vector<int> prime;
std::bitset<N> is_prime;

int Eratosthenes = [](int n) {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime.push_back(i);
        }
    }
    prime.emplace_back(N);
    prime.emplace_back(N);
    return 0;
}(N);

class Solution {
   public:
    vector<int> closestPrimes(int left, int right) {
        int p = -1, q = -1;
        auto i = std::lower_bound(prime.begin(), prime.end(), left) - prime.begin();
        for (; prime[i + 1] <= right; i++) {
            if (p < 0 || prime[i + 1] - prime[i] < q - p) {
                p = prime[i];
                q = prime[i + 1];
            }
        }
        return {p, q};
    }
};

int main(int argc, char** argv) {
    int left{19};
    int right{31};
    const auto ans{Solution{}.closestPrimes(left, right)};
    for (const auto& x : ans) {
        std::cout << std::format("{} ", x);
    }
    std::cout << std::format("\n");
}