#include <iostream>
using namespace std;
#include <cmath>

int main()
{
    int n = 0;
    cin >> n;
    int i = 0;
    for (i = n; i >= 1; i--)
    {
        if (floor(i * 1.08) == n)
        {
            cout << i << endl;
            break;
        }
        if (floor(i * 1.08) < n)
        {
            cout << ":(" << endl;
            break;
        }
    }
    return 0;
}