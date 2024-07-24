#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    int i = 0;
    int arr[1001] = {0};
    for (scanf("%d", &n); n + 1; scanf("%d", &n))
    {
        arr[n]++;
    }
    for (i = 1; i <= 1000; i++)
    {
        if (arr[i])
        {
            printf("%d %d\n", i, arr[i]);
        }
    }
    return 0;
}