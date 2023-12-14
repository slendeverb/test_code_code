#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    bool a[10];
    for (int i = 123; i < 333; i++)
    {
        memset(a, 0, sizeof(a));
        a[i % 10] = a[i / 10 % 10] = a[i / 100] = a[i * 2 % 10] = a[i * 2 / 10 % 10] = a[i * 2 / 100] = a[i * 3 % 10] = a[i * 3 / 10 % 10] = a[i * 3 / 100] = 1;
        int ret = 0;
        for (int i = 1; i <= 9; i++)
        {
            ret += a[i];
        }
        if (ret == 9)
        {
            printf("%d %d %d\n", i, i * 2, i * 3);
        }
    }
    return 0;
}