#include <iostream>
using namespace std;

int main()
{
    int a = 0, b = 0, c = 0;
    cin >> a >> b >> c;
    int count = 0;
    if (a % 2 == 1 || b % 2 == 1 || c % 2 == 1)
    {
        cout << 0 << endl;
    }
    else if (a == b && b == c)
    {
        cout << -1 << endl;
    }
    else
    {
        while (count < 10000)
        {
            int a1 = a / 2;
            int b1 = b / 2;
            int c1 = c / 2;
            a = b1 + c1;
            b = a1 + c1;
            c = a1 + b1;
            if (a % 2 == 1 || b % 2 == 1 || c % 2 == 1)
            {
                count++;
                break;
            }
            else
            {
                count++;
            }
        }
        if (count < 10000)
        {
            cout << count << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    return 0;
}