#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        double avg = 0.0, maxx = 2.0;
        if (n == 2)
        {
            avg = 1.0, maxx = 1.0;
        }
        else
        {
            avg = 2.0 * (n - 1) / n;
        }
        cout << fixed << setprecision(9) << avg << " " << maxx << "\n";
    }
    return 0;
}