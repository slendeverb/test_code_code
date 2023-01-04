#include <iostream>
#include <utility>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;

const int N = 5e5 + 10;
pair<ll, ll> p[N];
pair<ll, ll> ans;
ll t, n, m, k;
ll num, pret;

bool cmp(pair<ll, ll> a, pair<ll, ll> b)
{
    return a.first < b.first;
}

void solve()
{
    num = p[1].first - 1;
    for (int i = 1; i <= m; i++)
    {
        num = max(0ll, num - k * (p[i].first - pret - 1));
        if (p[i].first == t)
        {
            if (num != n)
            {
                cout << "Wrong Record"
                     << "\n";
                return;
            }
        }
        num += p[i].second;
        ll tmp = (num + k) / k;
        if (p[i].first > t)
        {
            if (tmp <= ans.second)
            {
                ans.second = tmp;
                ans.first = p[i].first;
            }
        }
        num = max(0ll, num - k);
        pret = p[i].first;
    }
    cout << ans.first << " " << ans.second << "\n";
}

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t >> n >> m >> k;
    for (int i = 1; i <= m; i++)
    {
        cin >> p[i].first >> p[i].second;
    }
    p[m + 1].first = t, p[m + 1].second = 0;
    m++;
    sort(p + 1, p + 1 + m, cmp);
    ans.second = LLONG_MAX;
    solve();
    return 0;
}