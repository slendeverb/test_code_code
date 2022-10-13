#include <iostream>
using namespace std;

int board[1000001] = {0};
int subscript[1000001] = {0};

int main()
{
    int n = 0;
    cin >> n;
    int i = 0;
    int j = 0;
    for (i = 1; i <= n; i++)
    {
        cin >> board[i];
    }
    for (i = 1; i <= n; i++)
    {
        subscript[i] = i;
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n - i; j++)
        {
            if (board[j] > board[j + 1])
            {
                int t = board[j];
                board[j] = board[j + 1];
                board[j + 1] = t;

                int t1 = subscript[j];
                subscript[j] = subscript[j + 1];
                subscript[j + 1] = t1;
            }
        }
    }
    int ret = 0;
    int max = 0;
    int flag = 1;
    int tmp = 0;
    for (i = 1; i < n; i++)
    {
        if (board[i] != board[i - 1])
        {
            flag = 1;
        }
        if (board[i] == board[i + 1])
        {
            if (flag)
            {
                tmp = subscript[i];
                flag = 0;
            }
            ret = subscript[i + 1] - tmp;
        }
        if (ret > max)
        {
            max = ret;
        }
    }
    cout << max << endl;
    return 0;
}