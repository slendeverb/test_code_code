#include <stdio.h>

int main()
{
    int num;
    while (1)
    {
        scanf("%o", &num);
        if (num == 0)
        {
            break;
        }
        else
        {
            printf("%d\n", num);
        }
    }
    return 0;
}