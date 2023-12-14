#include <bits/stdc++.h>
using namespace std;

void solve()
{
    long long a, b;
    cin >> a >> b;
    long long c = 180 * b;
    cout << c / __gcd(c, a) - 1 << "\n";
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}