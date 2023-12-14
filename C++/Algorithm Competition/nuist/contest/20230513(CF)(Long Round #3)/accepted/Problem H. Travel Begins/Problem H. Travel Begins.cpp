#include <iostream>
#include <cmath>
using namespace std;

const double c1 = 0.0000000001;
const double c2 = 0.5 - c1;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, k;
        cin >> n >> k;
        double a1 = n;
        double a2 = (k - 1) * c2;
        a1 -= a2;
        long long minn = 0;
        if (a1 <= 0.0)
        {
            minn = 0;
        }
        else
        {
            long long tmpa = a1;
            double decimala = a1 - (double)tmpa;
            if (decimala >= 0.5)
            {
                minn = minn + (long long)ceil(a1);
            }
            else
            {
                minn = minn + (long long)floor(a1);
            }
        }
        long long maxx = k - 1;
        double b1 = n;
        double b2 = (k - 1) * 0.5;
        b1 -= b2;
        if (b1 <= 0.0)
        {
            maxx = n * 2;
        }
        else
        {
            long long tmpb = b1;
            double decimalb = b1 - (double)tmpb;
            if (decimalb >= 0.5)
            {
                maxx = maxx + (long long)ceil(b1);
            }
            else
            {
                maxx = maxx + (long long)floor(b1);
            }
        }
        cout << minn << " " << maxx << "\n";
    }
    return 0;
}