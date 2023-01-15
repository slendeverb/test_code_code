#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
int n, m;

struct road
{
    int x;
    int y;
    int t;
} r[N];

bool cmp(road a, road b)
{
    return a.t < b.t;
}

int root[N];
void initset()
{
    for (int i = 0; i <= n; i++)
    {
        root[i] = i;
    }
}
int find(int x)
{
    return x == root[x] ? x : root[x] = find(root[x]);
}
bool merge(int x, int y)
{
    int dx = find(x);
    int dy = find(y);
    if (dx != dy)
    {
        root[dy] = dx;
        return true;
    }
    return false;
}

int main()
{
    cin >> n >> m;
    initset();
    for (int i = 1; i <= m; i++)
    {
        cin >> r[i].x >> r[i].y >> r[i].t;
    }
    sort(r + 1, r + 1 + m, cmp);
    int cnt = n;
    for (int i = 1; i <= m; i++)
    {
        if (merge(r[i].x, r[i].y))
        {
            cnt--;
        }
        if (cnt == 1)
        {
            cout << r[i].t << "\n";
            break;
        }
    }
    if (cnt > 1)
    {
        cout << -1 << "\n";
    }
    return 0;
}