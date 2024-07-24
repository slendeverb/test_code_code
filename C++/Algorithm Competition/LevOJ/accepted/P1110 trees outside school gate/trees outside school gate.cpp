#include <iostream>
using namespace std;

int main()
{
    int l = 0;
    int m = 0;
    int i = 0;
    while (scanf("%d %d", &l, &m) != EOF)
    {
        char tree[100001];
        for (i = 0; i <= l; i++)
        {
            tree[i] = 'y';
        }
        int start, end;
        while (m--)
        {
            scanf("%d %d", &start, &end);
            for (i = start; i <= end; i++)
            {
                tree[i] = 'n';
            }
        }
        int count = 0;
        for (i = 0; i <= l; i++)
        {
            if (tree[i] == 'y')
            {
                count++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}