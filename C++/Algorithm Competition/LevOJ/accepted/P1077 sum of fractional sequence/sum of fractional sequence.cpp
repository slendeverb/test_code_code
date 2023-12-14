#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int *p1 = new int[n];
        int *p2 = new int[n];
        p1[0] = 1;
        p1[1] = 2;
        p2[0] = 2;
        p2[1] = 3;
        int i = 0;
        double sum = 0;
        int count = 1;
        for (i = 2; i < n; i++)
        {
            p1[i] = p1[i - 1] + p1[i - 2];
            p2[i] = p2[i - 1] + p2[i - 2];
        }
        for (i = 0; i < n; i++)
        {
            if (count % 2 == 1)
            {
                sum += ((double)p2[i] / p1[i]);
            }
            else
            {
                sum -= ((double)p2[i] / p1[i]);
            }
            count++;
        }
        printf("%.4lf\n", sum);
    }
    return 0;
}