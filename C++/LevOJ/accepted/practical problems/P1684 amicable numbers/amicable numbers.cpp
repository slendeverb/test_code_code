#include <iostream>
using namespace std;

int sum_of_divisors(int n)
{
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }
    return sum;
}

bool is_armicable(int a, int b)
{
    return (sum_of_divisors(a) == b && sum_of_divisors(b) == a);
}

int main()
{
    int m;
    cin >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        if (is_armicable(a, b))
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
    return 0;
}