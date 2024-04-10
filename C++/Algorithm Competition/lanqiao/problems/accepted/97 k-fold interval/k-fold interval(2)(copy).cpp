#include <iostream>
using namespace std;
const int N = 100010;
// 因为是前缀和，数还是比较大的
long long a[N];
// 这里cnt[]最差情况也就所有数的余数相同（最大也就100000），不需要long long
int cnt[N];
int main() {
    int n, m;
    cin >> n >> m;
    // 余数为0说明本身就是可已被整除（可以模拟一下，如果初始为零会有有什么后果，这里就不说了）
    cnt[0] = 1;
    // 一般像求这种区间数量的，都非常大要long long
    long long res = 0;
    for (int i = 1; i <= n; i++) {
        // 自己前缀自己
        scanf("%d", &a[i]);
        a[i] += a[i - 1];
        // 加上之前和自己有相同余数的区间数量（两个构成一个可以被K整除的区间）
        res += cnt[a[i] % m];
        // 累加自己，因为后面还有可能有可以和他组成可被K整除的区间
        cnt[a[i] % m]++;
    }
    cout << res << endl;
    return 0;
}

// #include <iostream>
// using namespace std;

// typedef long long ll;

// const int N = 1e5 + 10;
// int n, k;
// ll pre[N], cnt[N];

// int main() {
//     cin >> n >> k;
//     for (int i = 0; i < n; ++i) {
//         cin >> pre[i];
//         if (i > 0)
//             pre[i] = pre[i] + pre[i - 1];
//         cnt[pre[i] % k]++;
//     }
//     ll res = cnt[0];
//     for (int i = 0; i < k; ++i) {
//         res += (cnt[i] * (cnt[i] - 1)) / 2;
//     }
//     cout << res << endl;
//     return 0;
// }