#include <iostream>
using namespace std;

int main()
{
    char ch[1001][100] = {0};
    int i = 0;
    for (i = 1;; i++)
    {
        scanf("%s", &ch[i]);
        if (getchar() == '\n')
        {
            break;
        }
    }
    printf("%d", i);
    return 0;
}