#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    if (n >= 90 && n <= 100)
    {
        printf("优\n");
    }
    else if (n >= 80 && n <= 89)
    {
        printf("良\n");
    }
    else if (n >= 70 && n <= 79)
    {
        printf("中\n");
    }
    else if (n >= 60 && n <= 69)
    {
        printf("及格\n");
    }
    else
    {
        printf("不及格\n");
    }
    return 0;
}