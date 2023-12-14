#include <stdio.h>

int main()
{
    int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf("----------------------------------------\n");
    int i = 0;
    printf("    ");
    for (i = 0; i < 9; i++)
    {
        printf("%4d", arr[i]);
    }
    printf("\n");
    printf("----------------------------------------\n");
    int j = 0;
    for (i = 0; i < 9; i++)
    {
        printf("%4d", arr[i]);
        for (j = 0; j < 9; j++)
        {
            printf("%4d", arr[i] * arr[j]);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
    return 0;
}