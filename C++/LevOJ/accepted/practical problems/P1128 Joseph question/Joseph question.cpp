#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    int m = 0;
    int i = 0;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        int *p = new int[n + 1];
        for (i = 1; i <= n; i++)
        {
            p[i] = i;
        }
        int count = m;
        int count1 = 0;
        int count2 = 0;
        i = 0;
        while (count2 < n)
        {
            count1 = 0;
            while (count1 < m)
            {
                if (++i <= n)
                {
                    ;
                }
                else
                {
                    i = 1;
                }
                if (p[i] != 0)
                {
                    count1++;
                }
            }
            printf("%d ", p[i]);
            p[i] = 0;
            count2++;
        }
        printf("\n");
    }
    return 0;
}