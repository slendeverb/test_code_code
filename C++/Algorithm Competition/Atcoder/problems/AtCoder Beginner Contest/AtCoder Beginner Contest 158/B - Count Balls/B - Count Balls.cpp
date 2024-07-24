#include <iostream>
using namespace std;
typedef long long ll;
int main()
{
    ll n, a, b;
    cin >> n >> a >> b;
    if (a == 0)
    {
        cout << 0 << "\n";
    }
    else if (a > n)
    {
        cout << n << "\n";
    }
    else if (a + b >= n)
    {
        cout << a << "\n";
    }
    else if (a + b < n)
    {
        if (n % (a + b) <= a)
        {
            cout << a * (n / (a + b)) + (n % (a + b)) << "\n";
        }
        else
        {
            cout << a * (n / (a + b)) + a << "\n";
        }
    }
    return 0;
}