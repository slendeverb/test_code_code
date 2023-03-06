#include <stdio.h>
#include <string.h>

const int N = 5010;

char *strStr(char *str, const char *target)
{
    if (!*target)
    {
        return str;
    }

    char *p1 = str;
    while (*p1)
    {
        char *p1_start = p1;
        char *p2 = (char *)target;

        while (*p1 && *p2 && (*p1 == *p2))
        {
            p1++;
            p2++;
        }
        if (!*p2)
        {
            return p1_start;
        }
        p1++;
    }
    return NULL;
}

int main()
{
    char str[N];
    char target[N];

    while (gets(str) != NULL)
    {
        gets(target);

        char *tmp = strStr(str, target);
        if (tmp == NULL)
        {
            printf("-1\n");
        }
        else
        {
            printf("%d\n", (tmp - str) + 1);
        }
    }
    return 0;
}