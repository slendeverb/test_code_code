#include <iostream>
#include <cmath>
using namespace std;

const int N = 2e5 + 10;
long long n, k, a[N], b[N];
bool satisfy[N][2];

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    satisfy[1][0] = satisfy[1][1] = true;
    for (int i = 2; i <= n; i++)
    {
        if (satisfy[i - 1][0])
        {
            if (abs(a[i] - a[i - 1]) <= k)
            {
                satisfy[i][0] = true;
            }
            if (abs(b[i] - a[i - 1]) <= k)
            {
                satisfy[i][1] = true;
            }
        }
        if (satisfy[i - 1][1])
        {
            if (abs(a[i] - b[i - 1]) <= k)
            {
                satisfy[i][0] = true;
            }
            if (abs(b[i] - b[i - 1]) <= k)
            {
                satisfy[i][1] = true;
            }
        }
    }
    if (satisfy[n][0] || satisfy[n][1])
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
    return 0;
}