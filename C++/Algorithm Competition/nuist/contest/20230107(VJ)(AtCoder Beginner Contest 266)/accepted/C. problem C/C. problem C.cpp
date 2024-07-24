#include <iostream>
#include <cmath>
using namespace std;

struct point
{
    int x;
    int y;
} a[4];

double dist(point a, point b)
{
    double dis = sqrt(abs(a.x - b.x) * abs(a.x - b.x) + abs(a.y - b.y) * abs(a.y - b.y));
    return dis;
}

double S(point a, point b, point c)
{
    double A = dist(a, b);
    double B = dist(b, c);
    double C = dist(a, c);
    double p = (A + B + C) / 2;
    double s = sqrt(p * (p - A) * (p - B) * (p - C));
    return s;
}

void solve(point a, point b, point c, point d)
{
    double s1 = S(a, b, c) + S(c, d, a);
    double s2 = S(b, c, d) + S(d, a, b);
    if (fabs(s1 - s2) < 1e-6)
    {
        cout << "Yes"
             << "\n";
    }
    else
    {
        cout << "No"
             << "\n";
    }
}

int main()
{
    for (int i = 0; i < 4; i++)
    {
        cin >> a[i].x >> a[i].y;
    }
    solve(a[0], a[1], a[2], a[3]);
    return 0;
}