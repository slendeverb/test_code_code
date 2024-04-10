#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, k;
int h[N], w[N];

bool check(int mid) {
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        count += (h[i] / mid) * (w[i] / mid);
    }
    return count >= k;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i] >> w[i];
    }
    int ans = 0;
    int l = 1, r = 1e5;
    int mid = 0;
    while (l <= r) {
        mid = ((r - l) >> 1) + l;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}