#include <iostream>
using namespace std;

int main()
{
    int t = 0;
    scanf("%d", &t);
    int i = 0;
    for (i = 0; i < t; i++)
    {
        int n = 0, m = 0;
        scanf("%d %d", &n, &m);
        int j = 0;
        int board[9][9] = {0};

        for (j = 0; j < m; j++)
        {
            int x = 0, y = 0;
            scanf("%d %d", &x, &y);
            board[x][y] = 1;
        }
        int r = 1;
        int c = 1;
        int flag = 0;
        for (r = 1; r <= n; r++)
        {
            for (j = 1; j <= n; j++)
            {
                if (board[r][j] == 1)
                {
                    break;
                }
            }
            if (j > n)
            {
                flag = 1;
                break;
            }
        }
        for (c = 1; c <= n; c++)
        {
            for (j = 1; j <= n; j++)
            {
                if (board[j][c] == 1)
                {
                    break;
                }
            }
            if (j > n)
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}