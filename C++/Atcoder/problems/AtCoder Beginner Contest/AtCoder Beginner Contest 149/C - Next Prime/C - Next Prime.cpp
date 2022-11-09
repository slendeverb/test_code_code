#include <iostream>
#include <cmath>
using namespace std;

int isprime(int n)
{
    if (n == 2 || n == 3)
    {
        return 1;
    }
    if (n % 6 != 1 && n % 6 != 5)
    {
        return 0;
    }
    for (int i = 5; i <= sqrt((double)n); i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int x = 0;
    cin >> x;
    for (int i = x;; i++)
    {
        if (isprime(i))
        {
            cout << i << endl;
            break;
        }
    }
    return 0;
}