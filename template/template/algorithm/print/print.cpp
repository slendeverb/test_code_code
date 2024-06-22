#include<iostream>
using namespace std;

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