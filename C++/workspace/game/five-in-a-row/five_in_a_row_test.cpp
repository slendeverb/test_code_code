#include <iostream>
#include <vector>
#include <windows.h>

const int board_size = 15;
std::vector<std::vector<int>> board(board_size, std::vector<int>(board_size, 0));

// 评估位置价值
int evaluate_position(const std::vector<std::vector<int>> &board, int player)
{
    int score = 0;

    // 检查水平方向
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
                score -= opponent_count * opponent_count * opponent_count;
            }
        }
    }

    // 检查垂直方向
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
                score -= opponent_count * opponent_count * opponent_count;
            }
        }
    }

    // 检查正对角线方向
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
                score -= opponent_count * opponent_count * opponent_count;
            }
        }
    }

    // 检查反对角线方向
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
                score -= opponent_count * opponent_count * opponent_count;
            }
        }
    }

    return score;
}

// AI决策
void ai_move(std::vector<std::vector<int>> &board)
{
    int best_value = -999999;
    std::pair<int, int> best_move;

    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = 1; // AI下棋
                int value = evaluate_position(board, 1);
                board[i][j] = 0; // 恢复空位

                if (value > best_value)
                {
                    best_value = value;
                    best_move = std::make_pair(i, j);
                }
            }
        }
    }

    if (best_value != -999999)
    {
        board[best_move.first][best_move.second] = 1; // AI下棋
        std::cout << "AI着棋:(" << best_move.first << "," << best_move.second << ")" << std::endl;
    }
}

// 玩家移动
void player_move(std::vector<std::vector<int>> &board)
{
    int row, col;
    std::cout << "请输入您的下棋位置（行 列）：";
    std::cin >> row >> col;

    while (row < 0 || row >= board_size || col < 0 || col >= board_size || board[row][col] != 0)
    {
        std::cout << "输入无效，请重新输入您的下棋位置（行 列）：";
        std::cin >> row >> col;
    }

    board[row][col] = -1; // 玩家下棋
}

// 判断胜负
bool check_winner(const std::vector<std::vector<int>> &board)
{
    // 检查水平方向
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size - 4; ++j)
        {
            int player = board[i][j];
            if (player != 0 && board[i][j + 1] == player && board[i][j + 2] == player &&
                board[i][j + 3] == player && board[i][j + 4] == player)
            {
                return true;
            }
        }
    }

    // 检查垂直方向
    for (int i = 0; i < board_size - 4; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            int player = board[i][j];
            if (player != 0 && board[i + 1][j] == player && board[i + 2][j] == player &&
                board[i + 3][j] == player && board[i + 4][j] == player)
            {
                return true;
            }
        }
    }

    // 检查正对角线方向
    for (int i = 0; i < board_size - 4; ++i)
    {
        for (int j = 0; j < board_size - 4; ++j)
        {
            int player = board[i][j];
            if (player != 0 && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player &&
                board[i + 3][j + 3] == player && board[i + 4][j + 4] == player)
            {
                return true;
            }
        }
    }

    // 检查反对角线方向
    for (int i = 4; i < board_size; ++i)
    {
        for (int j = 0; j < board_size - 4; ++j)
        {
            int player = board[i][j];
            if (player != 0 && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player &&
                board[i - 3][j + 3] == player && board[i - 4][j + 4] == player)
            {
                return true;
            }
        }
    }

    return false;
}

// 打印棋盘
void print_board(const std::vector<std::vector<int>> &board)
{
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            if (board[i][j] == 0)
            {
                std::cout << "- ";
            }
            else if (board[i][j] == 1)
            {
                std::cout << "X ";
            }
            else if (board[i][j] == -1)
            {
                std::cout << "O ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // 主游戏循环
    while (true)
    {
        player_move(board);

        print_board(board);

        if (check_winner(board))
        {
            std::cout << "玩家获胜！" << std::endl;
            break;
        }

        ai_move(board);

        print_board(board);

        if (check_winner(board))
        {
            std::cout << "AI获胜! " << std::endl;
            break;
        }
    }

    return 0;
}
