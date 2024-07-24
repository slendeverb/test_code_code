#include <stdio.h>
#include <math.h>
int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[10000] = {0};
    int i = 0;
    int a = 0;
    for (a = 2; a < n; a++)
    {
        int b = 1;
        for (i = 2; i <= sqrt(a); i++)
        {
            if (a % i == 0)
            {
                b = 0;
                break;
            }
        }
        if (b)
        {
            arr[a] = a;
        }
    }
    for (i = 0; i < n; i++)
    {
        int j = 0;
        for (j = 0; j < n; j++)
        {
            if (arr[i] + arr[j] == n)
            {
                printf("%d=%d+%d\n", n, arr[i], arr[j]);
                goto End;
            }
        }
    }
End:
    return 0;
}