#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    while (n > 0 && (n % 2 == 0 || n % 5 == 0))
    {
        if (n % 2 == 0)
        {
            n /= 2;
        }
        if (n % 5 == 0)
        {
            n /= 5;
        }
    }
    if (n == 1)
    {
        cout << "No\n";
    }
    else
    {
        cout << "Yes\n";
    }
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