#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, a[N];

void solve()
{
    cin >> n;
    int num1 = 0;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] == 1)
        {
            num1++;
        }
    }
    if (n == 1)
    {
        if (a[1] == 1)
        {
            ans = 1;
        }
        else
        {
            ans = 499122177;
        }
    }
    else if (num1 == n)
    {
        if (n & 1)
        {
            ans = 1;
        }
        else
        {
            ans = 0;
        }
    }
    else
    {
        ans = 499122177;
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}