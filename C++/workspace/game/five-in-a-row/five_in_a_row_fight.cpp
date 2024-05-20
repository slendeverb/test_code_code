#include <iostream>
#include <vector>
using namespace std;

const int board_size = 15;
vector<vector<int>> board(board_size, vector<int>(board_size, 0));

int evaluate_position(const vector<vector<int>> &board, int player)
{
    int score = 0;

    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size - 4; ++j)
        {
            int player_count = 0;
            int opponent_count = 0;
            for (int k = 0; k < 5; ++k)
            {
                if (board[i][j + k] == player)
                {
                    player_count++;
                }
                else if (board[i][j + k] == -player)
                {
                    opponent_count++;
                }
            }
            if (player_count > 0 && opponent_count == 0)
            {
                score += player_count * player_count * player_count;
            }
            else if (opponent_count > 0 && player_count == 0)
            {
                score -= opponent_count * opponent_count * opponent_count * opponent_count;
            }
        }
    }

    for (int i = 0; i < board_size - 4; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            int player_count = 0;
            int opponent_count = 0;
            for (int k = 0; k < 5; ++k)
            {
                if (board[i + k][j] == player)
                {
                    player_count++;
                }
                else if (board[i + k][j] == -player)
                {
                    opponent_count++;
                }
            }
            if (player_count > 0 && opponent_count == 0)
            {
                score += player_count * player_count * player_count;
            }
            else if (opponent_count > 0 && player_count == 0)
            {
                score -= opponent_count * opponent_count * opponent_count * opponent_count;
            }
        }
    }

    for (int i = 0; i < board_size - 4; ++i)
    {
        for (int j = 0; j < board_size - 4; ++j)
        {
            int player_count = 0;
            int opponent_count = 0;
            for (int k = 0; k < 5; ++k)
            {
                if (board[i + k][j + k] == player)
                {
                    player_count++;
                }
                else if (board[i + k][j + k] == -player)
                {
                    opponent_count++;
                }
            }
            if (player_count > 0 && opponent_count == 0)
            {
                score += player_count * player_count * player_count;
            }
            else if (opponent_count > 0 && player_count == 0)
            {
                score -= opponent_count * opponent_count * opponent_count * opponent_count;
            }
        }
    }

    for (int i = 4; i < board_size; ++i)
    {
        for (int j = 0; j < board_size - 4; ++j)
        {
            int player_count = 0;
            int opponent_count = 0;
            for (int k = 0; k < 5; ++k)
            {
                if (board[i - k][j + k] == player)
                {
                    player_count++;
                }
                else if (board[i - k][j + k] == -player)
                {
                    opponent_count++;
                }
            }
            if (player_count > 0 && opponent_count == 0)
            {
                score += player_count * player_count * player_count;
            }
            else if (opponent_count > 0 && player_count == 0)
            {
                score -= opponent_count * opponent_count * opponent_count * opponent_count;
            }
        }
    }

    return score;
}

pair<int, int> ai_move(vector<vector<int>> &board)
{
    int best_value = -999999;
    pair<int, int> best_move;

    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = 1;
                int value = evaluate_position(board, 1);
                board[i][j] = 0;

                if (value > best_value)
                {
                    best_value = value;
                    best_move = make_pair(i, j);
                }
            }
        }
    }

    if (best_value != -999999)
    {
        return best_move;
    }
}

int main()
{
    int turnID = 0;
    while (true)
    {
        int oi, oj;
        cin >> oi >> oj;
        if (oi != -1 && oj != -1)
        {
            board[oi][oj] = -1;
        }
        if (turnID == 0)
        {
            int i = 7, j = 7;
            if (board[7][7])
            {
                j = 8;
            }
            cout << i << ' ' << j << endl;
            board[i][j] = 1;
            turnID++;
            continue;
        }
        pair<int, int> best_move = ai_move(board);
        if (board[best_move.first][best_move.second])
        {
            continue;
        }
        else
        {
            cout << best_move.first << ' ' << best_move.second << endl;
            board[best_move.first][best_move.second] = 1;
        }
    }
    return 0;
}