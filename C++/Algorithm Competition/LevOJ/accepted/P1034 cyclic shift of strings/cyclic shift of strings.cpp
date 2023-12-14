#include <stdio.h>
#include <string.h>

char s[101];

void reverse_string(char *left, char *right)
{
    char tmp;
    while (left < right)
    {
        tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}

int main()
{
    int k;
    scanf("%d", &k);
    scanf("%s", s);
    int n = strlen(s);
    reverse_string(s, s + k - 1);
    reverse_string(s + k, s + n - 1);
    reverse_string(s, s + n - 1);
    printf("%s\n", s);
    return 0;
}