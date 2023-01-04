#include <bits/stdc++.h>
#define ll long long
#define PI 3.141592654
#define ull unsigned long long
const ll N = 1e6 + 5;
// ios::sync_with_stdio(false) ; cin.tie(0) ; cout.tie(0) ;
using namespace std;
pair<ll, ll> mo[N];
pair<ll, ll> mm;
ll pp = 0;
bool cmp(pair<ll, ll> a, pair<ll, ll> b)
{
    return a.first < b.first;
}
int main()
{
    ll t, n, m, k, i;
    scanf("%lld%lld%lld%lld", &t, &n, &m, &k);
    for (i = 1; i <= m; i++)
    {
        scanf("%lld%lld", &mo[i].first, &mo[i].second);
    }
    mo[m + 1].first = t, mo[m + 1].second = 0;
    m++;
    sort(mo + 1, mo + 1 + m, cmp);
    ll last = mo[1].second, lastime = 0, flag = 1;
    mm.second = 2e18;
    for (i = 1; i <= m; i++)
    {
        if (mo[i].first == t)
        {
            if (last != n)
            {
                flag = 0;
                break;
            }
        }
        last += mo[i].second;
        ll o = (last + k) / k;
        if (mo[i].first > t)
            if (o <= mm.second)
            {
                mm.second = o;
                mm.first = mo[i].first;
            }

        last = max(pp, last - k);
        lastime = mo[i].first;
    }
    if (!flag)
        printf("Wrong Record\n");
    else
        printf("%lld %lld\n", mm.first, mm.second);
    return 0;
}