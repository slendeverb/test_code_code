#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct gold
{
    int weight;
    int value;
    double unitvalue;
} g[110];

bool cmp(const gold &a, const gold &b)
{
    return a.unitvalue > b.unitvalue;
}

int main()
{
    int n, t;
    cin >> n >> t;
    for (int i = 1; i <= n; i++)
    {
        cin >> g[i].weight >> g[i].value;
        g[i].unitvalue = (double)g[i].value / g[i].weight;
    }

    sort(g + 1, g + 1 + n, cmp);

    double max_gold = 0;
    for (int i = 1; i <= n; i++)
    {
        if (t >= g[i].weight)
        {
            max_gold += g[i].value;
            t -= g[i].weight;
        }
        else
        {
            max_gold += g[i].unitvalue * t;
            break;
        }
    }

    cout << fixed << setprecision(2) << max_gold << "\n";
    return 0;
}