#include <iostream>
using namespace std;

typedef long long ll;
const ll p = 998244353;

int main()
{
    ll N;
    cin >> N;
    ll ans = 0;
    if (N >= p)
    {
        ans = N % p;
    }
    else
    {
        ans = ((N % p) + p) % p;
    }
    cout << ans << "\n";
    return 0;
}