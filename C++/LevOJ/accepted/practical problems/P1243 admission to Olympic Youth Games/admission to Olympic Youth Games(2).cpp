#include <iostream>
using namespace std;
#include <cstring>

struct ins
{
    int number;
    char country[100];
    int player;
    char area[100];
};
int main()
{
    int n, i, j;
    while (scanf("%d", &n) != EOF)
    {
        struct ins country[1000], t;
        for (i = 0; i < n; i++)
        {
            scanf("%d %s %d %s", &country[i].number, country[i].country, &country[i].player, country[i].area);
        }

        for (i = 0; i < n; i++)
        {
            if (strcmp(country[i].country, "China") == 0)
            {
                t = country[i];
                country[i] = country[n - 1];
                country[n - 1] = t;
            }
        }
        for (i = 0; i < n - 2; i++)
        {
            for (j = 0; j < n - i - 2; j++)
            {
                if (strcmp(country[j].country, country[j + 1].country) > 0)
                {
                    t = country[j];
                    country[j] = country[j + 1];
                    country[j + 1] = t;
                }
            }
        }
        for (i = 0; i < n; i++)
        {
            printf("%d %s %d %s\n", country[i].number, country[i].country, country[i].player, country[i].area);
        }
    }
    return 0;
}