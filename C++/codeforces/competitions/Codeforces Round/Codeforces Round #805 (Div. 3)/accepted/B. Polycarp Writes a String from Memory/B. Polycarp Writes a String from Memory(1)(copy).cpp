#include <stdio.h>

#define N 200001
char buffer[N];

int main()
{
    int t, d, ans;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", buffer);
        int alpha[26] = {0};
        d = ans = 0;
        for (int i = 0; buffer[i]; i++)
        {
            if (!alpha[buffer[i] - 'a'])
            {
                if (d == 3)
                {
                    ans++;
                    d = 1;
                    for (int i = 0; i < 26; i++)
                    {
                        alpha[i] = 0;
                    }
                }
                else
                {
                    d++;
                }
                alpha[buffer[i] - 'a']++;
            }
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}