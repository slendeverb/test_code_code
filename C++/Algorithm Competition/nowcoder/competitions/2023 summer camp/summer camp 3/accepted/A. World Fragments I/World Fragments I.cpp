#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    string tmp1, tmp2;
    cin >> tmp1 >> tmp2;
    long long x = 0, y = 0;
    for (auto ch : tmp1)
    {
        x = x * 2 + ch - '0';
    }
    for (auto ch : tmp2)
    {
        y = y * 2 + ch - '0';
    }
    if (x == y)
    {
        cout << "0\n";
    }
    else
    {
        if (x == 0)
        {
            cout << "-1\n";
        }
        else
        {
            cout << abs(x - y) << "\n";
        }
    }
    return 0;
}