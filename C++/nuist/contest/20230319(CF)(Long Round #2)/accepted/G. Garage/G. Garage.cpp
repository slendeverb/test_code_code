#include <iostream>
using namespace std;

long long n;

int main()
{
    cin >> n;
    if (n <= 3)
    {
        cout << 2 * n + 1 << "\n";
    }
    else
    {
        if ((n - 3) % 3 == 1)
        {
            cout << ((n - 1) / 3 + 1) * 4 << "\n";
        }
        else
        {
            cout << (n - (n - 1) / 3) * 2 + 1 << "\n";
        }
    }
    return 0;
}