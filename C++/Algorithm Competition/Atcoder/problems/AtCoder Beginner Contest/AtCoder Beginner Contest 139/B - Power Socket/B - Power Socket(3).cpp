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
        int i = 0;
        for (i = 0;; i++)
        {
            if (a + (a - 1) * i >= b)
            {
                break;
            }
        }
        cout << i + 1 << endl;
    }
    return 0;
}