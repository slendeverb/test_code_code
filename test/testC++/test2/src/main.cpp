#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 10;
int n;
std::vector<int> h(N);
std::vector<int> fac[N];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> h[i];
    }
    std::sort(h.begin() + 1, h.begin() + 1 + n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= h[i]; j++) {
            if (h[i] % j == 0) {
                fac[j].push_back(h[i]);
                if (h[i] / j != j) {
                    fac[h[i] / j].push_back(h[i]);
                }
            }
        }
    }
    auto gcd = [&](this auto&& self, int a, int b) -> int {
        if (b == 0) {
            return a;
        }
        return self(b, a % b);
    };
    auto find_abc = [&]() {
        for (int i = N; i >= 1; i--) {
            if (fac[i].size() >= 3) {
                int a = fac[i][0], b = fac[i][1], c = fac[i][2];
                if (gcd(gcd(a, b), c) == i) {
                    std::cout << a << " " << b << " " << c << "\n";
                    return;
                }
            }
        }
    };
    find_abc();
}

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
    solve();
}