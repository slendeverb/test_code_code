#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char s[500];
    scanf("%s", s);
    int i;
    for (i = 0; i < strlen(s); i++)
    {
        if (isupper(s[i]))
        {
            s[i] += ('a' - 'A');
        }
    }
    printf("%s\n", s);
    return 0;
}