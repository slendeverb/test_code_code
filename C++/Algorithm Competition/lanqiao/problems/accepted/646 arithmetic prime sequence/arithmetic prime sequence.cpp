#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

// 所有小于等差素数列的长度的素数的乘积就是该等差素数列的公差
// 若公差不是2的倍数，那么长度为10的等差数列里，必有一个2的倍数。
// 所以，公差必须是2的倍数。同理，公差必须是3、5、7的倍数，所以求2、3、5、7的最小公倍数即可。
// 而正因为2、3、5、7都是素数，所以它们的最小公倍数就是它们的积。
// 对于长度为k的素数等差数列，它们的公差能被小于k的所有素数整除。

bool is_prime(int n)
{
    if (n == 2 | n == 3)
    {
        return true;
    }
    if (n % 6 != 1 && n % 6 != 5)
    {
        return false;
    }
    for (int i = 5; i <= sqrt(n); i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

int prime[10000];

int main()
{
    int count = 0;
    int pos = 0;
    for (int i = 2; pos < 10000; i++)
    {
        if (is_prime(i))
        {
            prime[pos++] = i;
        }
    }

    for (int i = 2, tmp = 0; tmp < 10000; i = prime[++tmp])
    {
        for (int j = 1; j < 1e6; j++)
        {
            count = 0;
            for (int k = i;; k += j)
            {
                if (is_prime(k))
                {
                    count++;
                    if (count == 10)
                    {
                        cout << j << "\n";
                        exit(0);
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
    return 0;
}