#include <iostream>
using namespace std;

const int maxn = 1e4 + 10;
const int exp3[] = {0, 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};
char u[maxn][maxn];

void separated_universe(int x, int y, int sz, bool is_space)
{
    if (is_space)
    {
        for (int i = 0; i < exp3[sz]; i++)
        {
            for (int j = 0; j < exp3[sz]; j++)
            {
                u[x + i][y + j] = ' ';
            }
        }
        return;
    }

    if (sz == 1)
    {
        u[x][y] = 'X';
        return;
    }

    separated_universe(x, y, sz - 1, false);
    separated_universe(x, y + exp3[sz - 1], sz - 1, true);
    separated_universe(x, y + 2 * exp3[sz - 1], sz - 1, false);
    separated_universe(x + exp3[sz - 1], y, sz - 1, true);
    separated_universe(x + exp3[sz - 1], y + exp3[sz - 1], sz - 1, false);
    separated_universe(x + exp3[sz - 1], y + 2 * exp3[sz - 1], sz - 1, true);
    separated_universe(x + 2 * exp3[sz - 1], y, sz - 1, false);
    separated_universe(x + 2 * exp3[sz - 1], y + exp3[sz - 1], sz - 1, true);
    separated_universe(x + 2 * exp3[sz - 1], y + 2 * exp3[sz - 1], sz - 1, false);
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        separated_universe(0, 0, n, false);
        for (int i = 0; i < exp3[n]; i++)
        {
            for (int j = 0; j < exp3[n]; j++)
            {
                printf("%c", u[i][j]);
            }
            cout << "\n";
        }
        cout << "-\n";
    }

    return 0;
}