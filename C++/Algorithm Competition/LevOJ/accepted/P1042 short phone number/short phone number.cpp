#include <stdio.h>

char phone_number[11];

int main()
{
    scanf("%s", phone_number);
    printf("6");
    int i;
    for (i = 6; i < 11; i++)
    {
        printf("%c", phone_number[i]);
    }
    printf("\n");
    return 0;
}