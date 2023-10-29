#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

void solve()
{
    vector<string> board;
    for (int i = 0; i < 3; i++)
    {
        string s;
        cin >> s;
        board.emplace_back(s);
    }
    int cntX = 0, cnt0 = 0, cntDot = 0;
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
            {
                cntX++;
            }
            else if (board[i][j] == '0')
            {
                cnt0++;
            }
            else
            {
                cntDot++;
            }
        }
    }

    if (board[0][0] == board[0][1] && board[0][1] == board[0][2])
    {
        if (board[0][0] == 'X')
        {
            flag = 1;
        }
        else if (board[0][0] == '0')
        {
            flag = 2;
        }
    }
    else if (board[1][0] == board[1][1] && board[1][1] == board[1][2])
    {
        if (board[1][0] == 'X')
        {
            flag = 1;
        }
        else if (board[1][0] == '0')
        {
            flag = 2;
        }
    }
    else if (board[2][0] == board[2][1] && board[2][1] == board[2][2])
    {
        if (board[2][0] == 'X')
        {
            flag = 1;
        }
        else if (board[2][0] == '0')
        {
            flag = 2;
        }
    }
    else if (board[0][0] == board[1][0] && board[1][0] == board[2][0])
    {
        if (board[0][0] == 'X')
        {
            flag = 1;
        }
        else if (board[0][0] == '0')
        {
            flag = 2;
        }
    }
    else if (board[0][1] == board[1][1] && board[1][1] == board[2][1])
    {
        if (board[0][1] == 'X')
        {
            flag = 1;
        }
        else if (board[0][1] == '0')
        {
            flag = 2;
        }
    }
    else if (board[0][2] == board[1][2] && board[1][2] == board[2][2])
    {
        if (board[0][2] == 'X')
        {
            flag = 1;
        }
        else if (board[0][2] == '0')
        {
            flag = 2;
        }
    }
    else if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
        {
            flag = 1;
        }
        else if (board[0][0] == '0')
        {
            flag = 2;
        }
    }
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'X')
        {
            flag = 1;
        }
        else if (board[0][2] == '0')
        {
            flag = 2;
        }
    }

    if (cnt0 > cntX || cnt0 == cntX && flag == 1 || cntX == cnt0 + 1 && flag == 2 || cntX - cnt0 > 1)
    {
        cout << "illegal\n";
    }
    else if (cntDot == 0 && !flag)
    {
        cout << "draw\n";
    }
    else if (flag)
    {
        if (flag == 1)
        {
            cout << "the first player won\n";
        }
        else if (flag == 2)
        {
            cout << "the second player won\n";
        }
    }
    else if (cntX == cnt0 + 1)
    {
        cout << "second\n";
    }
    else if (cnt0 == cntX)
    {
        cout << "first\n";
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("./test/in.txt", "r", stdin), freopen("./test/out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}