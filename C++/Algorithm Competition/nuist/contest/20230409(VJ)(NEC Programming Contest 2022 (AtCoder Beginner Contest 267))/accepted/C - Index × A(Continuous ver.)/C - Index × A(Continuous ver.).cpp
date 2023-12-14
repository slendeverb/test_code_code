#include <iostream>
#include <climits>
using namespace std;

const int maxn = 2e5 + 10;
long long a[maxn];
long long b[maxn];
long long ans = LLONG_MIN, tmp;
int n, m;

int main()
{
    cin >> n >> m;
    b[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i] + b[i - 1];
    }
    for (int i = 1; i <= m; i++)
    {
        tmp += (i * a[i]);
    }
    ans = tmp;
    for (int i = m + 1; i <= n; i++)
    {
        tmp = tmp + (m * a[i]) - (b[i - 1] - b[i - 1 - m]);
        ans = max(ans, tmp);
    }
    cout << ans << "\n";
    return 0;
}