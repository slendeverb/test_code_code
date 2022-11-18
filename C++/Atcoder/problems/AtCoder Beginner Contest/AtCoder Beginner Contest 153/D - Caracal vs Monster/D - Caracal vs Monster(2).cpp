#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    ll h = 0;
    cin >> h;
    ll ans = 1;
    ll tmp = 1;
    if (h == 1)
    {
        cout << ans << "\n";
    }
    else
    {
        while (h > 1)
        {
            tmp *= 2;
            ans += tmp;
            h /= 2;
        }
        cout << ans << "\n";
    }
    return 0;
}