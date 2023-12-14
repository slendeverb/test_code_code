#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        int x;
        cin >> x;
        sum -= x;
    }
    cout << sum << "\n";
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