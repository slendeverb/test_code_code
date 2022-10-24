#include <iostream>
using namespace std;
#include <math.h>
double Pi = acos(-1.0);
typedef long long ll;
double eps = 1e-4;

double fgcd(double x, double y)
{
    while (fabs(x) > eps && fabs(y) > eps)
    {
        if (x > y)
            x -= floor(x / y) * y;
        else
            y -= floor(y / x) * x;
    }
    return x + y;
}

double my_distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}
int main()
{
    double x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    double a = my_distance(x1, y1, x2, y2);
    double b = my_distance(x1, y1, x3, y3);
    double c = my_distance(x2, y2, x3, y3);
    double p = (a + b + c) / 2;
    double S = sqrt(p * (p - a) * (p - b) * (p - c));
    double R = a * b * c / (4 * S);
    double alpha = acos(1 - a * a / (2 * R * R));
    double beta = acos(1 - b * b / (2 * R * R));
    double gamma = acos(1 - c * c / (2 * R * R));
    double angle = fgcd(fgcd(alpha, beta), fabs(2*Pi-alpha-beta));
    double n = 2 * Pi / angle;
    double Area = R * R * sin(angle) * n / 2;
    printf("%.6lf\n", Area);
    return 0;
}