#include <bits/stdc++.h>
using namespace std;

void fun(char *a)
{
    char *p1 = a, *p2 = a + strlen(a) - 1;
    while (*p1 == '*')
    {
        p1++;
    }
    p1++;
    while (*p2 == '*')
    {
        p2--;
    }
    p2++;
    char *p3 = p1;
    while (p3 < p2)
    {
        if (*p3 == '*')
        {
            p3++;
        }
        else
        {
            *p1 = *p3;
            p1++, p3++;
        }
    }
    *p1 = '\0';
}
int main()
{
    char s[81];
    FILE *in, *out;
    int i;
    printf("Enter a string :\n");
    gets(s);
    fun(s);
    printf("The string after deleted:\n");
    puts(s);
    return 0;
}