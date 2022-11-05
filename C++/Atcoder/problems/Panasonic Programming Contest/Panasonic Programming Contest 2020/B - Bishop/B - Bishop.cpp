#include <iostream>
using namespace std;

int main()
{
    long long r = 0, c = 0;
    cin >> r >> c;
    if (r == 1 || c == 1)
    {
        cout << 1 << endl;
    }
    else
    {
        cout << (r * c + 1) / 2 << endl;
    }
    return 0;
}