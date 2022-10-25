#include <iostream>
using namespace std;

int main()
{
    int i = 0;
    for (i = 100; i < 1000; i++)
    {
        int m = i;
        int sum = 0;
        while (m)
        {
            int tmp = m % 10;
            sum += tmp * tmp * tmp;
            m /= 10;
        }
        if (sum == i)
        {
            cout << i << endl;
        }
    }
    return 0;
}