#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;

int main()
{
    ll n, k;
    cin >> n >> k;
    ll ans = min(n % k, abs(n % k - k));
    cout << ans << endl;
    return 0;
}