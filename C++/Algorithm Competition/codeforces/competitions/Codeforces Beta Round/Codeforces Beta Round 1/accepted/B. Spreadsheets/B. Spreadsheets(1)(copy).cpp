#include <iostream>
using namespace std;
typedef long long ll;

void change(int x)
{
    if (x)
    {
        change((x - 1) / 26);
        putchar('A' + (x - 1) % 26);
    }
}

int main(void)
{
    int T;
    char s[105];
    for (scanf("%d", &T); T; T--)
    {
        int row, col;
        scanf("%s", s);
        if (sscanf(s, "%*[A-Z]%d%*[A-Z]%d", &row, &col) == 2)
        {
            change(col);
            printf("%d\n", row);
        }
        else
        {
            col = 0;
            for (int i = 0; isupper(s[i]); ++i)
                col = col * 26 + s[i] - 'A' + 1;
            printf("R%dC%d\n", row, col);
        }
    }
    return 0;
}
