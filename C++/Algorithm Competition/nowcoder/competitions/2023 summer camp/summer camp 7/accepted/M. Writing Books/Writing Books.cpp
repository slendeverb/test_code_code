#include <iostream>
using namespace std;

int n;

void solve()
{
    cin >> n;
    int cnt = 0, tmpn = n;
    while (tmpn)
    {
        tmpn /= 10;
        cnt++;
    }
    long long ans = 0;
    long long p = 1;
    for (int i = 1; i < cnt; i++)
    {
        ans += i * 9 * p;
        p *= 10;
    }
    ans += cnt * (n - p + 1);
    cout << ans << "\n";
}

int main()
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