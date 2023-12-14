#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
static const double EPS = 1e-4;
static const double PI = acos(-1.0);
struct Point
{
    double x, y;
} point[4];
double dis[4];
double gcd(double x, double y)
{
    while (fabs(x) > EPS && fabs(y) > EPS)
    {
        if (x > y)
            x -= floor(x / y) * y;
        else
            y -= floor(y / x) * x;
    }
    return x + y;
}
int main()
{
    for (int i = 1; i <= 3; i++)
        cin >> point[i].x >> point[i].y;
    dis[1] = sqrt((point[1].x - point[2].x) * (point[1].x - point[2].x) + (point[1].y - point[2].y) * (point[1].y - point[2].y));
    dis[2] = sqrt((point[1].x - point[3].x) * (point[1].x - point[3].x) + (point[1].y - point[3].y) * (point[1].y - point[3].y));
    dis[3] = sqrt((point[2].x - point[3].x) * (point[2].x - point[3].x) + (point[2].y - point[3].y) * (point[2].y - point[3].y));
    Point v1 = {point[2].x - point[1].x, point[2].y - point[1].y}, v2 = {point[3].x - point[1].x, point[3].y - point[1].y};
    double s = (v1.x * v2.y - v1.y * v2.x) / 2;
    double r = dis[1] * dis[2] * dis[3] / 4 / s;
    double a = acos((dis[2] * dis[2] + dis[3] * dis[3] - dis[1] * dis[1]) / (2 * dis[2] * dis[3]));
    double b = acos((dis[1] * dis[1] + dis[3] * dis[3] - dis[2] * dis[2]) / (2 * dis[1] * dis[3]));
    double c = acos((dis[1] * dis[1] + dis[2] * dis[2] - dis[3] * dis[3]) / (2 * dis[1] * dis[2]));
    double n = PI / gcd(gcd(a, b), c);
    cout << fixed << setprecision(8) << n / 2 * r * r * sin(2 * PI / n) << endl;
    return 0;
}
