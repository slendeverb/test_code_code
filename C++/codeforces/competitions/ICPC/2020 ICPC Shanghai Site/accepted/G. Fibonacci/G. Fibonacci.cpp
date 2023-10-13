#include <bits/stdc++.h>
using namespace std;

// 斐波那契额数列的规律是 odd, odd, even, odd, odd, even ......
// 求所有的 even + odd 和 even + even 共有多少

void solve()
{
    long long n;
    cin >> n;
    long long even = n / 3;
    long long odd = n - even;
    cout << (even * (even - 1) / 2 + even * odd) << "\n";
    // cout << (n * (n - 1) / 2) - (odd * (odd - 1) / 2) << "\n";
}

int main()
{
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}