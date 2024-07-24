#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 3e5 + 10;

struct node
{
    int LP, index;
} a[maxn];

bool cmp(const node &x, const node &y)
{
    if (x.LP == 0 || y.LP == 0)
    {
        if (x.LP == y.LP)
        {
            return x.index < y.index;
        }
        else if (x.LP == 0)
        {
            return true;
        }
        else if (y.LP == 0)
        {
            return false;
        }
    }
    if (x.LP != y.LP)
    {
        return x.LP > y.LP;
    }
    else
    {
        return x.index < y.index;
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i].LP;
            a[i].index = i;
            a[i].LP %= k;
        }
        sort(a + 1, a + 1 + n, cmp);
        for (int i = 1; i <= n; i++)
        {
            cout << a[i].index << " ";
        }
        cout << "\n";
    }
    cout.flush();
    return 0;
}