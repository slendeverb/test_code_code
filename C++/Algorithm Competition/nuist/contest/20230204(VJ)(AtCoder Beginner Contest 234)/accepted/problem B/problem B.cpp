#include <iostream>
#include <cmath>
using namespace std;

const int N = 110;

struct Point
{
    int x;
    int y;
} point[N];

double dist(Point a, Point b)
{
    return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> point[i].x >> point[i].y;
    }
    double maxx = 0.0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i != j)
            {
                maxx = max(maxx, dist(point[i], point[j]));
            }
        }
    }
    printf("%.6lf\n", maxx);
    return 0;
}