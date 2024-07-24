#include <stdio.h>

int main()
{
    int i = 0;
    int count = 0;
    for (i = 100; i <= 200; i++)
    {
        if (i % 3 != 0)
        {
            printf("%6d", i);
            count++;
        }
        if (count == 6)
        {
            printf("\n");
            count = 0;
        }
    }
    return 0;
}