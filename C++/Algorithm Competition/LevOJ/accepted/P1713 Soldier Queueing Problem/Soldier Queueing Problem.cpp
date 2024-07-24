#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 1e4 + 10;

int x[maxn], y[maxn];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }
    sort(y, y + n);
    int midy = (n % 2 ? y[(n - 1) / 2] : (y[n / 2] + y[n / 2 - 1]) / 2);

    long long ans = 0;

    sort(x, x + n);

    for (int i = 0; i < n; i++)
    {
        x[i] -= i;
    }
    sort(x, x + n);

    int midx = (n % 2 ? x[(n - 1) / 2] : (x[n / 2] + x[n / 2 - 1]) / 2);
    for (int i = 0; i < n; i++)
    {
        ans += abs(x[i] - midx) + abs(y[i] - midy);
    }

    cout << ans << "\n";
    return 0;
}