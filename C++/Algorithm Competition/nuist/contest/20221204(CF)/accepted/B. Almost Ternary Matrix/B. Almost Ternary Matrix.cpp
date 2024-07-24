#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef long long LL;
#define ll LL

int t, n, m;

const int N = 3e5 + 10;

int a[4][4] = {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 0}, {1, 0, 0, 1}};

void solve()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << a[i % 4][j % 4] << " ";
        }
        cout << "\n";
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