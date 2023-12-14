#include <iostream>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        char arr[9][9] = {0};
        for (int i = 1; i <= 8; i++)
        {
            cin >> arr[i];
        }
        for (int i = 1; i <= 8; i++)
        {
            for (int j = 1; j <= 8; j++)
            {
                if (arr[i - 1][j - 2] == '#' && arr[i - 1][j] == '#' && arr[i + 1][j - 2] == '#' && arr[i + 1][j - 2] == '#')
                {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
    return 0;
}