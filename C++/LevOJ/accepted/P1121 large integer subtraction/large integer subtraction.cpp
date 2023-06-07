#include <stdio.h>
#include <string.h>

char arr1[210], arr2[210];
int a[210], b[210], minus[210];

int main()
{
    while (scanf("%s%s", arr1, arr2) != EOF)
    {
        int len_a = strlen(arr1);
        int len_b = strlen(arr2);
        for (int i = 0; i <= len_a - 1; i++)
        {
            a[len_a - i] = arr1[i] - '0';
        }
        for (int i = 0; i <= len_b - 1; i++)
        {
            b[len_b - i] = arr2[i] - '0';
        }
        int pos = 1;
        int carry = 0;
        while (pos <= len_a)
        {
            minus[pos] = a[pos] - b[pos] - carry;
            if (minus[pos] < 0)
            {
                carry = 1;
                minus[pos] += 10;
            }
            else
            {
                carry = 0;
            }
            pos++;
        }
        while (minus[pos] == 0)
        {
            pos--;
        }
        for (int i = pos; i >= 1; i--)
        {
            printf("%d", minus[i]);
        }
        printf("\n");
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(minus, 0, sizeof(minus));
    }
    return 0;
}