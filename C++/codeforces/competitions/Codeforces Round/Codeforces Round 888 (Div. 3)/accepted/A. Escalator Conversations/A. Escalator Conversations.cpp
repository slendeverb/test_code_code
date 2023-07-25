#include <iostream>
using namespace std;

const int maxn = 60;
int h[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, k, H;
        cin >> n >> m >> k >> H;
        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> h[i];
            if (h[i] != H && abs(h[i] - H) % k == 0 && abs(h[i] - H) <= (m - 1) * k)
            {
                ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}