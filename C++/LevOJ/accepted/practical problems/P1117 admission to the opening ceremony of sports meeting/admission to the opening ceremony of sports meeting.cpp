#include <iostream>
using namespace std;
#include <cstring>

int sort_by_name(const void *str1, const void *str2)
{
    return strcmp((const char *)str1, (const char *)str2);
}
int main()
{
    int n = 0;
    cin >> n;
    int i = 0;
    char ch[100][20] = {0};
    for (i = 0; i < n; i++)
    {
        scanf("%s", &ch[i]);
    }
    qsort(ch, n, sizeof(ch[0]), sort_by_name);
    for (i = 0; i < n; i++)
    {
        if (strcmp(ch[i], "China"))
        {
            printf("%s\n", ch[i]);
        }
    }
    cout << "China" << endl;
    return 0;
}