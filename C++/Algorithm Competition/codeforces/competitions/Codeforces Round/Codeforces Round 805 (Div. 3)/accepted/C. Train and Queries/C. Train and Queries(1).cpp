#include <iostream>
using namespace std;

struct K
{
    int k1;
    int k2;
};
int main()
{
    int t = 0;
    scanf("%d", &t);
    while (t--)
    {
        int n = 0;
        int k = 0;
        struct K q = {0, 0};
        scanf("%d %d", &n, &k);
        int *p = new int[n + 1];
        int i = 0;
        for (i = 0; i < n; i++)
        {
            scanf("%d", &p[i]);
        }
        while (k--)
        {
            scanf("%d %d", &q.k1, &q.k2);
            int flag = 0;
            for (i = 0; i < n - 1; i++)
            {
                int j = 0;
                if (p[i] == q.k1)
                {
                    for (j = i + 1; j < n; j++)
                    {
                        if (p[j] == q.k2)
                        {
                            flag = 1;
                            break;
                        }
                    }
                }
            }
            if (flag)
            {
                printf("YES\n");
            }
            else
            {
                printf("NO\n");
            }
        }
    }
    return 0;
}