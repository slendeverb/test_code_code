#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

int main()
{
    int n;
    cin >> n;
    vector<pair<ll, ll>> a(n), tmp, Tmp;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].second;
    }

    vector<ll> Sx, Sy, len;
    ll sum = 0, ans = 0; // ans维护重叠部分，最后答案就是sum-2*ans

    for (auto [x, y] : a)
    {
        sum += abs(x - y);
        // 分成两类
        if (x < y)
        {
            tmp.emplace_back(x, y);
        }
        else if (x > y)
        {
            Tmp.emplace_back(y, x);
        }
    }

    sort(tmp.begin(), tmp.end());
    ll r = -1e18;
    // 消除正向相互包络关系——不难发现正向相互包络关系不会对答案有任何正贡献
    for (auto x : tmp)
    {
        if (x.second <= r)
        {
            continue;
        }
        r = x.second;
        Sx.push_back(x.first), Sy.push_back(x.second);
        len.push_back(x.second - x.first);
    }

    auto query = [&](ll x, ll y)
    {
        ll n = Sx.size();
        ll ret = 0;
        ll l = upper_bound(Sx.begin(), Sx.end(), x) - Sx.begin();
        ll r = lower_bound(Sy.begin(), Sy.end(), y) - Sy.begin();
        if (l > 0)
        {
            ret = max(ret, min(y, Sy[l - 1] - x)); // 找反序交叉
        }
        if (r < n)
        {
            ret = max(ret, y - max(x, Sx[r])); // 找反序交叉
        }
        if (r > l)
        {
            ret = max(ret, *max_element(len.begin() + l, len.begin() + r)); // 找反序包络
        }
        return ret;
    };

    for (auto x : Tmp)
    {
        ans = max(ans, query(x.first, x.second));
    }
    cout << sum - 2 * ans << "\n";
    return 0;
}