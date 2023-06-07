#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int i = 0;
        int j = 0;
        if (n == 1)
        {
            printf("%d\n", 1);
        }
        else
        {
            for (i = 4;; i += 2)
            {
                j = i;
                int count = 0;
                while (1)
                {
                    if ((i = i - (((double)i / 2) + 1)) >= 1)
                    {
                        count++;
                    }
                    else
                    {
                        i = j;
                        count++;
                        break;
                    }
                }
                if (count == n)
                {
                    printf("%d\n", i);
                    break;
                }
            }
        }
    }
    return 0;
}