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
ll a[N];
ll b[N];

void solve()
{
    int count = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    b[count++] = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] != a[i - 1])
        {
            b[count++] = a[i];
        }
    }
    if (count == 1 || count == 0)
    {
        cout << "YES"
             << "\n";
    }
    else
    {
        int sum = 0;
        if (b[0] < b[1])
        {
            sum++;
        }
        for (int i = 0; i < count - 1; i++)
        {
            if (b[i] < b[i - 1] && b[i] < b[i + 1])
            {
                sum++;
            }
        }
        if (b[count - 1] < b[count - 2])
        {
            sum++;
        }
        if (sum > 1)
        {
            cout << "NO"
                 << "\n";
        }
        else
        {
            cout << "YES"
                 << "\n";
        }
    }
}

int main()
{
    IOS;
    cin >> t;
    while (t--)
        solve();
    return 0;
}