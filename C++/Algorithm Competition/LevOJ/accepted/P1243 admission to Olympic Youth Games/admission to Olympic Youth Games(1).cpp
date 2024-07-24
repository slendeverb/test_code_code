#include <iostream>
using namespace std;
#include <cstring>

typedef struct CountryInfo
{
    int x;
    char country[100];
    int num;
    char countinent[100];
} CI;

int sort_by_name(const void *str1, const void *str2)
{
    return strcmp(((CI *)str1)->country, ((CI *)str2)->country);
}

int main()
{
    int n = 0;
    cin >> n;
    CI c[1000];
    int i = 0;
    CI c1[1] = {0};
    for (i = 0; i < n; i++)
    {
        scanf("%d %s %d %s", &c[i].x, &c[i].country, &c[i].num, &c[i].countinent);
    }
    qsort(c, n, sizeof(CI), sort_by_name);
    for (i = 0; i < n; i++)
    {
        if (strcmp(c[i].country, "China"))
        {
            printf("%d %s %d %s\n", c[i].x, c[i].country, c[i].num, c[i].countinent);
        }
        else
        {
            c1[1] = c[i];
        }
    }
    printf("%d %s %d %s\n", c1[1].x, c1[1].country, c1[1].num, c1[1].countinent);
    return 0;
}