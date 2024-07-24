#include <iostream>
using namespace std;

const int maxn = 1e4 + 10;
struct blanket
{
    int a, b, g, k;
} m[maxn];

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> m[i].a >> m[i].b >> m[i].g >> m[i].k;
    }

    int x, y;
    cin >> x >> y;
    int ans = -1;
    for (int i = n; i >= 1; i--)
    {
        if (x >= m[i].a && x <= m[i].a + m[i].g && y >= m[i].b && y <= m[i].b + m[i].k)
        {
            ans = i;
            break;
        }
    }
    cout << ans << "\n";
    return 0;
}