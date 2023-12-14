#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int x;
        cin >> x;
        if (x == 0)
        {
            cout << 0 << "\n";
            continue;
        }
        long long low = x, high = x;
        long long y = 0;
        bool flag = 0;
        while (low < 1e17)
        {
            low *= 10;
            high *= 10;
            high += 9;
            y = ceil(sqrt(low * 1.0));
            if (y * y <= high)
            {
                flag = 1;
                cout << y << "\n";
                break;
            }
        }
        if (!flag)
        {
            cout << -1 << "\n";
        }
    }
    return 0;
}