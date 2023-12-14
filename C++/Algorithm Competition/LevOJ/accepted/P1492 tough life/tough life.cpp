#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n, k;
    while (cin >> n >> k)
    {
        double tmp = 200.0 / (n - k);
        if (tmp > 20 || tmp < 0)
        {
            cout << "Impossible\n";
        }
        else
        {
            long long m = tmp;
            if (200 % (n - k) != 0)
            {
                m++;
            }
            cout << m << "\n";
        }
    }
    return 0;
}