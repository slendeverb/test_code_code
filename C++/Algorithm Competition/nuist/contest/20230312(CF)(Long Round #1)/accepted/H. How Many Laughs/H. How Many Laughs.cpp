#include <iostream>
#include <set>
using namespace std;

#define int long long

const int N = 30;
int n, x;
int a[N];
long long ans;
set<long long> s;

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0);
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1;; j++)
        {
            int tmp = j * a[i];
            if (tmp <= x)
            {
                s.insert(j * a[i]);
            }
            else
            {
                break;
            }
        }
    }
    ans = s.size();
    cout << ans << "\n";
    return 0;
}