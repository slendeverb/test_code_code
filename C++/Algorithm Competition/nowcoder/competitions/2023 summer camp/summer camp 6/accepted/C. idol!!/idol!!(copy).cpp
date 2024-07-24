#include <iostream>
using namespace std;

__int128_t solve(long long n)
{
    __int128_t ans = 0;
    if (n & 1)
    {
        __int128_t k = 5;
        while (k <= n)
        {
            ans += ((n / k) + 1) / 2;
            k *= 5;
        }
        --n;
    }
    __int128_t k = 5;
    while (k <= n)
    {
        __int128_t m = n / k;
        ans += (m - 1) * m * (k / 2) / 2;
        ans += (2 * ((m - 1) / 2)) * ((m + 1) / 2) / 2;
        __int128_t l = m * k, r = n;
        if (((l | r) & 1) == 0)
        {
            ++r;
        }
        ans += m * (r - l + 1) / 2;
        k *= 5;
    }
    return ans;
}

void print(__int128_t x)
{
    if (x < 0)
    {
        x = -x;
        putchar('-');
    }
    if (x > 9)
    {
        print(x / 10);
    }
    putchar(x % 10 + '0');
}

int main()
{
    long long n;
    cin >> n;
    print(solve(n));
    return 0;
}