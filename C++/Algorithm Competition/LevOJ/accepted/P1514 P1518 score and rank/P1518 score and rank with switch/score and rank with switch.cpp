#include <stdio.h>

int main()
{
    int score = 0;
    while (scanf("%d", &score) != EOF)
    {
        if (score == -1)
        {
            break;
        }
        else
        {
            switch (score / 10)
            {
            case 10:
                printf("优\n");
                break;
            case 9:
                printf("优\n");
                break;
            case 8:
                printf("良\n");
                break;
            case 7:
                printf("中\n");
                break;
            case 6:
                printf("及格\n");
                break;
            case 5:
            case 4:
            case 3:
            case 2:
            case 1:
            case 0:
                printf("不及格\n");
                break;
            }
        }
    }
    return 0;
}