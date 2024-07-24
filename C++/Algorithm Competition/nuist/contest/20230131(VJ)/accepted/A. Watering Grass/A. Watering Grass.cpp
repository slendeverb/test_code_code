#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int n, l, w;

const int N = 1e4 + 10;

struct Sprinkler
{
    double position;
    double radius;
} s[N];

bool cmp(Sprinkler a, Sprinkler b)
{
    if (a.position != b.position)
    {
        return a.position < b.position;
    }
    return a.radius > b.radius;
}

int main()
{
    while (~scanf("%d%d%d", &n, &l, &w))
    {
        int k = 0;
        double maxx = -1;
        for (int i = 0; i < n; i++)
        {
            double x, y;
            cin >> x >> y;
            if (y * 2 < w)
            {
                continue;
            }
            else
            {
                s[k].position = x - sqrt(y * y - w * w / 4.0);
                s[k].radius = x + sqrt(y * y - w * w / 4.0);
                if (s[k].radius > maxx)
                {
                    maxx = s[k].radius;
                }
                k++;
            }
        }
        sort(s, s + k, cmp);
        if (s[0].position > 0 || maxx < l)
        {
            cout << -1 << "\n";
            continue;
        }
        bool flag = true;
        double x = 0.0;
        int ans = 0;
        while (x < l)
        {
            double y = x;
            for (int i = 0; i < k; i++)
            {
                if (s[i].radius > x && s[i].position <= y)
                {
                    x = s[i].radius;
                }
            }
            if (y == x && y < l)
            {
                flag = false;
                break;
            }
            ans++;
        }
        if (flag)
        {
            cout << ans << "\n";
        }
        else
        {
            cout << -1 << "\n";
        }
    }
    return 0;
}