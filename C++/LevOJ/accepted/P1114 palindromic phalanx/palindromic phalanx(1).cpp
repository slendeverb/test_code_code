#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    int step[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    int next[4] = {1, 2, 3, 0};
    int i = 0, j = 0;
    while (scanf("%d", &n) != EOF)
    {
        int arr[20][20] = {0};
        for (i = 0; i <= n + 1; i++)
        {
            arr[i][n + 1] = arr[n + 1][i] = arr[0][i] = arr[i][0] = 1;
        }
        i = 1;
        int s = 1;
        j = n;
        int k = 0;
        for (s = 1; s <= n * n; s++)
        {
            arr[i][j] = s;
            if (arr[i + step[k][0]][j + step[k][1]])
            {
                k = next[k];
            }
            i += step[k][0];
            j += step[k][1];
        }
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}