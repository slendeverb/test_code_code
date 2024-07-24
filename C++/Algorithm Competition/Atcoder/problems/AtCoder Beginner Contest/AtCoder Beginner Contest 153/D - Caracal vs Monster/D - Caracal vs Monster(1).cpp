#include <iostream>
using namespace std;
typedef long long ll;
ll solve(ll n)
{
    if (n == 1)
    {
        return 1;
    }
    return 1 + solve(n / 2) + solve(n / 2);
}
int main()
{
    ll h = 0;
    cin >> h;
    cout << solve(h) << "\n";
    return 0;
}