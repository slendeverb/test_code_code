#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        double n, m, d;
        cin >> n >> m >> d;
        if (fabs(ceil(m / n) - d) < 1e-4 || m / n > d)
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
    return 0;
}