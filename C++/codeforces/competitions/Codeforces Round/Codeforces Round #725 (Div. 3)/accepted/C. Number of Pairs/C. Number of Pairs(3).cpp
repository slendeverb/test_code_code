#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve()
{
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    ll ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += upper_bound(arr.begin(), arr.end(), r - arr[i]) - arr.begin();
        ans -= lower_bound(arr.begin(), arr.end(), l - arr[i]) - arr.begin();
        if (2 * arr[i] >= l && 2 * arr[i] <= r)
        {
            ans--;
        }
    }
    cout << ans / 2 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}