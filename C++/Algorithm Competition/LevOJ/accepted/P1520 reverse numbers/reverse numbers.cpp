#include <stdio.h>

int reverse(int x)
{
    int ret = 0;
    while (x > 0)
    {
        ret = ret * 10 + x % 10;
        x /= 10;
    }
    return ret;
}
int main()
{
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    printf("%d\n%d\n", reverse(a), reverse(b));
    return 0;
}