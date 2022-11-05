#include <iostream>
#include <map>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e6 + 10, mod = 1e9 + 7;

int T;

void solve()
{
    int n, m;
    scanf("%d", &n);

    int res = 0, x;
    map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x);
        if (!mp[x])
            res++;
        mp[x]++;
    }

    int f = 0;
    for (auto it : mp)
    {
        if (it.second >= 2)
            f += (it.second - 1);
    }

    if (f % 2)
        res--;

    printf("%d\n", res);
}

int main()
{
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}
