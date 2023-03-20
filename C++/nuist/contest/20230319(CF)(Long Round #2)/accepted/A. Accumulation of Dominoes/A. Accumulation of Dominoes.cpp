#include <iostream>
using namespace std;

long long n, m;

int main()
{
    cin >> n >> m;
    long long ans = 0;
    if (m == 1)
    {
        ans = (n - 1) * m;
    }
    else
    {
        ans = (m - 1) * n;
    }
    cout << ans << "\n";
    return 0;
}