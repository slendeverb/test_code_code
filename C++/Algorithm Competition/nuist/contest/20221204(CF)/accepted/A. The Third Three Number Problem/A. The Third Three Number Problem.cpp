#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef long long LL;
#define ll LL

ll t, n, m;

const int N = 3e5 + 10;

void solve()
{
    cin >> n;
    if (n % 2 == 1)
    {
        cout << -1 << "\n";
    }
    else
    {
        int half = n / 2;
        printf("%d %d %d\n", 0, half, half);
    }
}

int main()
{
    // IOS;
    cin >> t;
    while (t--)
        solve();
    return 0;
}