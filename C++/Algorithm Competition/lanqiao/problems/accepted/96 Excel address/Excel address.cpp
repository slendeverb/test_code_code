#include <bits/stdc++.h>
using namespace std;

const int N{INT_MAX};
int n;

void solve() {
    cin >> n;
    std::vector<char> ans;
    while (n) {
        --n;
        ans.push_back(n % 26 + 'A');
        n /= 26;
    }
    for (int i = ans.size() - 1; i >= 0; --i) {
        std::cout << ans[i];
    }
}

int main() {
    solve();
    return 0;
}