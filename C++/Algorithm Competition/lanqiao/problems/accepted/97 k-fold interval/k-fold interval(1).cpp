#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, k;
long long a[N];
int sameMod[N];

void solve() {
    cin >> n >> k;
    long long ans = 0;
    sameMod[0] = 1;
    //实际上就是其它余数的计数如果只有一个，没有能跟它组成区间的话，其它sameMod的初始值为0就可以避免多算，而余数为0它自己就是一个区间可以作为答案
    //实际上就是用组合法求解时需要加上能直接整除k的所有前缀和自己单独作为区间的值
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i - 1];
        ans += sameMod[a[i] % k];
        ++sameMod[a[i] % k];
    }
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// const int N = 1e5 + 5;
// int n, k;
// std::vector<int> a;
// std::vector<long long> parSum;

// void solve() {
//     std::cin >> n >> k;
//     a.resize(n + 1);
//     parSum.resize(n + 1);
//     for (int i = 1; i <= n; ++i) {
//         std::cin >> a[i];
//     }
//     for (int i = 1; i <= n; ++i) {
//         parSum[i] = parSum[i - 1] + a[i];
//     }
//     long long ans = 0;
//     for (int i = 1; i <= n; ++i) {
//         for (int j = i; j <= n; ++j) {
//             if ((parSum[j] - parSum[i - 1]) % k == 0) {
//                 ++ans;
//             }
//         }
//     }
//     std::cout << ans << "\n";
// }

// int main() {
//     solve();
//     return 0;
// }