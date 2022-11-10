#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, d, x, sum = 0, day, a;
    cin >> n >> d >> x;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        day = 1;
        while (day <= d)
        {
            sum++;
            day += a;
        }
    }
    cout << sum + x << "\n";
    return (0);
}