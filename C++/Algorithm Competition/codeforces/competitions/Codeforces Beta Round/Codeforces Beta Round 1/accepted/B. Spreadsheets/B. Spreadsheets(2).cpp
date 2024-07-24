#include <iostream>
using namespace std;

void toAlpha(int x)
{
    if (x)
    {
        toAlpha((x - 1) / 26);
        putchar((x - 1) % 26 + 'A');
    }
}
int main()
{
    int n = 0;
    char s[105]={0};
    cin >> n;
    while (n--)
    {
        int row, col, tmp;
        scanf("%s", s);
        int ret = sscanf(s, "%*[A-Z]%d%*[A-Z]%d", &row, &col);
        if (ret == 2)
        {
            toAlpha(col);
            printf("%d\n", row);
        }
        else
        {
            col = 0;
            for (int i = 0; isupper(s[i]); i++)
            {
                col = col * 26 + s[i] - 'A' + 1;
            }
            printf("R%dC%d\n", row, col);
        }
    }
    return 0;
}