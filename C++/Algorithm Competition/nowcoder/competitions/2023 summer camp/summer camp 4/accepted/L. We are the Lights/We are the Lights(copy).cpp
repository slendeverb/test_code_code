#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1e6 + 5;

long long ans;
char c1[10], c2[5];
int a[MAXN], la[MAXN << 1];

int main()
{
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= q; i++)
    {
        int x;
        scanf("%s%d%s", c1, &x, c2);
        if (c1[0] == 'r')
        {
            a[i] |= 2, x += m;
        }
        if (c2[1] == 'n')
        {
            a[i] |= 1;
        }
        a[la[x]] = -1, la[x] = i;
    }
    for (int i = q; i >= 1; i--)
    {
        if (a[i] == -1)
        {
            continue;
        }
        if (a[i] & 2)
        {
            if (a[i] & 1)
            {
                ans += m;
            }
            --n;
        }
        else
        {
            if (a[i] & 1)
            {
                ans += n;
            }
            --m;
        }
    }
    printf("%lld\n", ans);
    return 0;
}