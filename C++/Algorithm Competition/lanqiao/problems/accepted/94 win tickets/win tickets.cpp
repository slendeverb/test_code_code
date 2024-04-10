#include <bits/stdc++.h>
using namespace std;

const int N{105};
int n;
int a[N];
int vis[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof(vis));
        int num = 0;
        int pos = i - 1;
        int count = 0;
        int res = 0;
        while (num <= n && count < n) {
            ++pos;
            if (pos > n) {
                pos = 1;
            }
            if (vis[pos]) {
                continue;
            }
            ++num;
            if (a[pos] == num) {
                vis[pos] = 1;
                num = 0;
                ++count;
                res += a[pos];
            }
        }
        ans = std::max(ans, res);
    }
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}