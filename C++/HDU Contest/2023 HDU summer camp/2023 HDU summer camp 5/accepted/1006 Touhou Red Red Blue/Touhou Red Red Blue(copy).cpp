#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

const int maxs = 1e5 + 5;

int f[maxs][20];
char s[maxs];

#define ID(a, b) (((a) << 2) | (b))

int main()
{
    int T;
    scanf("%d", &T);
    memset(f[0], 0x8f, sizeof(f[0]));
    f[0][0] = 0;
    while (T--)
    {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        for (int i = 1; i <= len; i++)
        {
            int c = (s[i] == 'R' ? 1 : (s[i] == 'G' ? 2 : 3));
            for (int a = 0; a <= 3; a++)
            {
                for (int b = 0; b <= 3; b++)
                {
                    f[i][ID(a, b)] = f[i - 1][ID(a, b)];
                }
            }
            for (int a = 0; a <= 3; a++)
            {
                for (int b = 0; b <= 3; b++)
                {
                    if (a == b && b == c)
                    {
                        int F = f[i - 1][ID(a, b)] + 1;
                        for (int d = 1; d <= 3; d++)
                        {
                            f[i][d] = max(f[i][d], F);
                        }
                    }
                    else if (a && b && c && a != b && a != c && b != c)
                    {
                        int F = f[i - 1][ID(a, b)];
                        for (int d = 1; d <= 3; d++)
                        {
                            for (int e = 1; e <= 3; e++)
                            {
                                f[i][ID(d, e)] = max(f[i][ID(d, e)], F);
                            }
                        }
                    }
                    else
                    {
                        f[i][ID(b, c)] = max(f[i][ID(b, c)], f[i - 1][ID(a, b)]);
                    }
                }
            }
        }
        int ans = 0;
        for (int a = 0; a <= 3; a++)
        {
            for (int b = 0; b <= 3; b++)
            {
                ans = max(ans, f[len][ID(a, b)]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}