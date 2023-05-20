#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int maxt = 1e5 + 10;

double ans[maxt];

// 两端和两个路灯中间最暗,设两个路灯间的距离为L,两个路灯中间的点亮度为d/[(L/2)^2],两端也要是这个亮度,那么路灯与两端的距离为L/(sqrt(8)),(k-1)*L+2*L/(sqrt(8))=n

int main()
{
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        long long n, k, d;
        cin >> n >> k >> d;
        double l = 2 * n / (2 * (k - 1) + sqrt(2));
        double ans = 8 * d / (l * l);
        cout << fixed << setprecision(6) << ans << "\n";
    }
    return 0;
}