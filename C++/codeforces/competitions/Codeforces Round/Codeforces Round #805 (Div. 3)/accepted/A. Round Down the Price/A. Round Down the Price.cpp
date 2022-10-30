#include <iostream>
using namespace std;
#include <math.h>

int main()
{
    int t = 0;
    cin >> t;
    int i = 0;
    while (t--)
    {
        int m = 0;
        cin >> m;
        for (i = 10; i >= 0; i--)
        {
            if (m - pow(10, i) >= 0)
            {
                printf("%.0lf\n", m - pow(10, i));
                break;
            }
        }
    }
    return 0;
}