#include <iostream>
#include <fstream>
using namespace std;

int baseChangeDigitSum(int base, int num)
{
    int res = 0;
    while (num)
    {
        res += num % base;
        num /= base;
    }
    return res;
}

void solve()
{
    int count = 0;
    for (int i = 1;; i++)
    {
        if (i % baseChangeDigitSum(2, i) != 0)
        {
            continue;
        }
        if (i % baseChangeDigitSum(8, i) != 0)
        {
            continue;
        }
        if (i % baseChangeDigitSum(10, i) != 0)
        {
            continue;
        }
        if (i % baseChangeDigitSum(16, i) != 0)
        {
            continue;
        }
        count++;
        if (count == 2023)
        {
            std::cout << i << std::endl;
            return;
        }
    }
}

int main()
{
    solve();
    return 0;
}