#include <iostream>
#include <string>
using namespace std;

char board[3][3];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string ans = "DRAW";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> board[i][j];
            }
        }
        if (board[0][0] != '.')
        {
            if (board[0][1] == board[0][0] && board[0][1] == board[0][2] || board[1][0] == board[0][0] && board[1][0] == board[2][0])
            {
                ans = board[0][0];
            }
        }
        if (board[1][1] != '.')
        {
            if (board[1][1] == board[1][0] && board[1][2] == board[1][1] || board[1][1] == board[0][1] && board[2][1] == board[1][1] || board[0][0] == board[1][1] && board[2][2] == board[1][1] || board[0][2] == board[1][1] && board[2][0] == board[1][1])
            {
                ans = board[1][1];
            }
        }
        if (board[2][2] != '.')
        {
            if (board[2][0] == board[2][1] && board[2][1] == board[2][2] || board[0][2] == board[1][2] && board[1][2] == board[2][2])
            {
                ans = board[2][2];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}