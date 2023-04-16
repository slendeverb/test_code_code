#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>
using namespace std;

const int maxn = 2e5 + 10;
int a[maxn];
map<int, int, less<int>> m;
bool vis[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, A, B;
        cin >> n >> A >> B;
        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        sort(a + 1, a + 1 + n);
        for (int i = 1; i <= n; i++)
        {
            if (m[a[i]] == 0)
            {
                m[a[i]] = upper_bound(a + 1, a + 1 + n, a[i]) - lower_bound(a + 1, a + 1 + n, a[i]);
            }
        }
        auto it = m.begin();
        if (it->second <= 1)
        {
            if (n % 2 == 0)
            {
                ans = A * n / 2;
            }
            else
            {
                ans = -1;
            }
        }
        else if (it->second == n)
        {
            ans = -1;
        }
        else
        {
            auto it = m.begin();
            if (n % 2 == 1)
            {
                ans += B;
                n--;
                it->second--;
                it = m.begin();
            }
            while (it->second > n - (it->second))
            {
                ans += B;
                n--;
                it->second--;
                it = m.begin();
            }
            while (n >= 2 && n % 2 == 0 && it->second >= 2)
            {
                long long tmp1 = ans + (A * n / 2);
                long long tmp2 = ans + (2 * B) + (A * (n - 2) / 2);
                ans = min(tmp1, tmp2);
                if (ans == tmp1)
                {
                    break;
                }
                else if (ans == tmp2)
                {
                    n -= 2;
                    it->second -= 2;
                    it = m.begin();
                }
            }
            it = m.begin();
            if (it->second < 2)
            {
                ans += (A * n / 2);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}