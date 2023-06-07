#include <stdio.h>
#include <string.h>

char arr1[210];
char arr2[210];
int a[210], b[210], sum[210];

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
        while (pos <= len_a || pos <= len_b)
        {
            sum[pos] = a[pos] + b[pos] + carry;
            carry = sum[pos] / 10;
            sum[pos] %= 10;
            pos++;
        }
        sum[pos] = carry;
        while (sum[pos] == 0)
        {
            pos--;
        }
        for (int i = pos; i >= 1; i--)
        {
            printf("%d", sum[i]);
        }
        printf("\n");
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(sum, 0, sizeof(sum));
    }
    return 0;
}