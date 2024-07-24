#include <iostream>
using namespace std;

int A, sum, ret;

int gcd(int x, int y)
{
    int t;
    while (t = x % y)
    {
        x = y;
        y = t;
    }
    return y;
}

int main()
{
    cin >> A;
    for (int i = 2; i < A; i++)
    {
        int tmp = A;
        ret = 0;
        while (tmp)
        {
            ret += (tmp % i);
            tmp /= i;
        }
        sum += ret;
    }
    int tmp1 = gcd(sum, A - 2);
    sum /= tmp1;
    cout << sum << "/" << (A - 2) / tmp1 << "\n";
    return 0;
}