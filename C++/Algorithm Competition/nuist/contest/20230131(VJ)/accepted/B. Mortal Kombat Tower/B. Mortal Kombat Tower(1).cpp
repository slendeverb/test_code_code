#include <iostream>
#include <cstring>
using namespace std;

const int N = 2e5 + 10;
int t, n;
int ans[N][2], boss[N];

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--)
    {
        memset(ans, 0x3f, sizeof(ans));
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> boss[i];
        }
        ans[0][0] = 0;
        ans[1][1] = boss[1];
        for (int i = 2; i <= n; i++)
        {
            ans[i][1] = min(ans[i - 1][0] + boss[i], ans[i - 2][0] + boss[i - 1] + boss[i]);
            ans[i][0] = min(ans[i - 1][1], ans[i - 2][1]);
        }
        cout << min(ans[n][0], ans[n][1]) << "\n";
    }
    return 0;
}