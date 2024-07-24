#include <iostream>
using namespace std;
#include <cmath>

int issquare(int n)
{
    for (int i = 1; i <= sqrt((double)n); i++)
    {
        if (n == i * i)
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    int a = 0, b = 0;
    cin >> a >> b;
    int p = 1;
    int b1 = b;
    while (b1)
    {
        b1 /= 10;
        p *= 10;
    }
    int sum = a * p + b;
    if (issquare(sum))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}