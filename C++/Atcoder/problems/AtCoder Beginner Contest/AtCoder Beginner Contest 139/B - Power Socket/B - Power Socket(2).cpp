#include <iostream>
using namespace std;

int main()
{
    int a = 0, b = 0;
    cin >> a >> b;
    if (b == 1)
    {
        cout << 0 << endl;
    }
    else
    {
        if (b % a == 0)
        {
            cout << b / a << endl;
        }
        else
        {
            cout << b / a + 1 << endl;
        }
    }
    return 0;
}