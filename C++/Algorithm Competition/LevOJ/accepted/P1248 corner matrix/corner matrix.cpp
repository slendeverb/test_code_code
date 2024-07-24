#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int i = 0, j = 0, k = 0;
        int arr[30][30] = {0};
        for (i = 1; i <= n; i++)
        {
            j = i;
            k = i;
            for (; j <= n; j++)
            {
                arr[i][j] = i;
            }
            for (; k <= n; k++)
            {
                arr[k][i] = i;
            }
        }
        for (i = 1; i <= n; i++)
        {
            printf("%d", 1);
            for (j = 2; j <= n; j++)
            {
                printf(" %d", arr[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}