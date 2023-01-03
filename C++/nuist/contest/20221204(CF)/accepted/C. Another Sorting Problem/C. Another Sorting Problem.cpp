#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
typedef long long LL;
#define ll LL
int t, n, m;
const int N = 1e6 + 10;

struct S
{
    int x;
    string p;
} s[N];
bool cmp(S x, S y)
{
    return x.p < y.p;
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        s[i].x = i;
        cin >> s[i].p;
        for (int j = 0; j < m; j++)
        {
            if (j % 2 == 1)
            {
                s[i].p[j] = 'Z' - (s[i].p[j] - 'A');
            }
        }
    }
    sort(s + 1, s + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        cout << s[i].x << " ";
    }
    cout << "\n";
}

int main()
{
    // IOS;
    // cin >> t;
    // while (t--)
    solve();
    return 0;
}