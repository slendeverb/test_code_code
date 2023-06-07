#include <stdio.h>
#include <string.h>

char s[55];

int main()
{
    while (scanf("%s", s) != EOF)
    {
        int len = strlen(s);
        int i = len - 1;
        if (s[0] == '-')
        {
            printf("-");
            while (s[i] == '0')
            {
                i--;
            }
            for (; i > 0; i--)
            {
                printf("%c", s[i]);
            }
        }
        else if (s[0] == '0')
        {
            printf("0");
        }
        else
        {
            for (i = len - 1; i >= 0; i--)
            {
                while (s[i] == '0')
                {
                    i--;
                }
                for (; i >= 0; i--)
                {
                    printf("%c", s[i]);
                }
            }
        }
        printf("\n");
    }
    return 0;
}