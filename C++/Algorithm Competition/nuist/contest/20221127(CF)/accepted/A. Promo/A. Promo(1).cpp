#include <iostream>
using namespace std;

const int N = 2e5 + 10;
int p[N];
int sort(const void *str1, const void *str2)
{
    return *((int *)str2) - *((int *)str1);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    qsort(p, n, sizeof(int), sort);
    for (int i = 0; i < q; i++)
    {
        int ans = 0;
        int x, y;
        cin >> x >> y;
        for (int j = x - 1; j >= x - y; j--)
        {
            ans += p[j];
        }
        cout << ans << "\n";
    }
    return 0;
}