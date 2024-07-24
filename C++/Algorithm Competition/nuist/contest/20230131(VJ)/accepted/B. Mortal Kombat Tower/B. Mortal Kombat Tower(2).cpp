#include <iostream>
using namespace std;

int t, n, x;

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--)
    {
        int cnt = 0, ans = 0;
        cin >> n;
        cin >> ans;
        for (int i = 1; i < n; i++)
        {
            cin >> x;
            if (x == 1)
            {
                cnt++;
            }
            else
            {
                ans += cnt / 3;
                cnt = 0;
            }
        }
        cout << ans + cnt / 3 << "\n";
    }
    return 0;
}