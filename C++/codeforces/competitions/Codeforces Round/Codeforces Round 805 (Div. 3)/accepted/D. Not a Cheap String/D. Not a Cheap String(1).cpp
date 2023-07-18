#include <iostream>
using namespace std;
#include <cstring>

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        char w[1001] = {0};
        int p = 0;
        int alpha[27] = {0};
        int i = 0;
        scanf("%s", &w);
        scanf("%d", &p);
        int min = 100;
        int sum = 0;
        int max = 0;
        for (i = 0; i < strlen(w); i++)
        {
            alpha[w[i] - 'a' + 1]++;
            if (w[i] - 'a' + 1 < min)
            {
                min = w[i] - 'a' + 1;
            }
            if (w[i] - 'a' + 1 > max)
            {
                max = w[i] - 'a' + 1;
            }
            sum += w[i] - 'a' + 1;
        }
        if (min > p)
        {
            printf("\n");
        }
        else if (sum <= p)
        {
            printf("%s\n", w);
        }
        else
        {
            int count = 0;
            if (sum - min <= p)
            {
                max = min;
            }
            for (i = max; i >= 1;)
            {
                while (alpha[i] != 0)
                {
                    sum = sum - i;
                    count++;
                    int j = strlen(w) - 1;
                    while (count)
                    {
                        if (w[j] == i - 1 + 'a')
                        {
                            w[j] = '0';
                            count--;
                        }
                        j--;
                    }
                    alpha[i]--;
                    if (sum <= p)
                    {
                        goto End;
                    }
                }
                i--;
            }
        End:
            for (i = 0; i < strlen(w); i++)
            {
                if (w[i] != '0')
                {
                    printf("%c", w[i]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}