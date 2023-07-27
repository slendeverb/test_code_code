#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10;

struct score
{
    int a, b;
} s[maxn];

bool cmp(const score &x, const score &y)
{
    return x.a - y.b > y.a - x.b;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> s[i].a >> s[i].b;
        }
        sort(s + 1, s + 1 + n, cmp);
        long long ans = 0;
        for (int i = 1; i <= n; i += 2)
        {
            ans += s[i].a - s[i + 1].b;
        }
        cout << ans << "\n";
    }
    return 0;
}