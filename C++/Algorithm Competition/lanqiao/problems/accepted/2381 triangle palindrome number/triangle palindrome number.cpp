#include <iostream>
using namespace std;

bool isPalindrome(int a)
{
    int temp = a;
    int b = 0;
    while (temp)
    {
        b = b * 10 + temp % 10;
        temp /= 10;
    }
    if (b == a)
    {
        return true;
    }
    return false;
}

void solve()
{
    int x = 0;
    for (int i = 1;; i++)
    {
        x += i;
        if (x <= 20220514)
        {
            continue;
        }
        if (isPalindrome(x))
        {
            std::cout << x << std::endl;
            break;
        }
    }
}

int main()
{
    solve();
    return 0;
}