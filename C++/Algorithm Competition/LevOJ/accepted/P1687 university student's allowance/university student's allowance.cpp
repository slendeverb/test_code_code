#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int m;
    double rate = 1 + (0.0171 / 12);
    while (cin >> m)
    {
        double ans = 0;
        for (int i = 1; i <= 48; i++) // 原本为sum*=rate,sum-=m;
        {
            ans += m;
            ans /= rate;
        }
        cout << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}