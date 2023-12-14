#include <iostream>
using namespace std;

const int maxn = 150;
int a[maxn][maxn];

int main()
{
    int n;
    while (cin >> n)
    {
        int row = 1, col = 1, dir = 1, pos = 1;
        for (int i = 1; i <= n * n; i++)
        {
            a[row][col] = i;

            pos++;
            if (pos > n)
            {
                dir *= -1;
                pos = 1;
                col++;
            }
            else
            {
                if (dir == 1)
                    row++;
                else
                    row--;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}