#include <bitset>
#include <iostream>

#define BOARD_SIZE 15
#define DIRECTIONS_COUNT 3

#define PLAYER_MOVE 1
#define OPPONENT_MOVE -1

#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL_DOWN_RIGHT 2
#define DIAGONAL_DOWN_LEFT 3

#define PLAYER_WIN_SCORE 100000
#define FOUR_COUNT_SCORE 1000
#define THREE_COUNT_SCORE 100
#define TWO_COUNT_SCORE 10

const short DIRECTIONS[DIRECTIONS_COUNT] = {-1, 0, 1};

short grid[BOARD_SIZE][BOARD_SIZE] = {};

bool isGameOver(short player);
bool isWinningMove(short player, short row, short col);
bool isPotentialWinningMove(short player, short row, short col);
short calculateMoveScore(short row, short col);
short calculateLineScore(short row, short col, short dRow, short dCol);

int main()
{
    short turnID = 0;
    while (true)
    {
        int row, col;
        scanf("%d%d", &row, &col);
        if (row != -1 && col != -1)
            grid[row][col] = OPPONENT_MOVE;
        if (turnID == 0)
        {
            int i = BOARD_SIZE / 2, j = BOARD_SIZE / 2;
            if (grid[i][j])
                j++;
            std::cout << i << ' ' << j << std::endl;
            grid[i][j] = PLAYER_MOVE;
            turnID++;
            continue;
        }
        short bestMoveRow = -1, bestMoveCol = -1;
        short maxScore = -1;

        for (short i = 0; i < BOARD_SIZE; i++)
        {
            for (short j = 0; j < BOARD_SIZE; j++)
            {
                if (grid[i][j] == 0)
                {
                    // 防守策略：检查对手是否有潜在的胜利路径
                    if (isPotentialWinningMove(OPPONENT_MOVE, i, j))
                    {
                        std::cout << i << ' ' << j << std::endl;
                        grid[i][j] = PLAYER_MOVE;
                        goto end;
                    }

                    // 进攻策略：检查自己是否有潜在的胜利路径
                    if (isPotentialWinningMove(PLAYER_MOVE, i, j))
                    {
                        // 选择具有最高得分的进攻位置
                        short score = calculateMoveScore(i, j);
                        if (score > maxScore)
                        {
                            maxScore = score;
                            bestMoveRow = i;
                            bestMoveCol = j;
                        }
                    }
                }
            }
        }

        // 如果找到了最佳进攻位置，则选择该位置下棋
        if (bestMoveRow != -1 && bestMoveCol != -1)
        {
            std::cout << bestMoveRow << ' ' << bestMoveCol << std::endl;
            grid[bestMoveRow][bestMoveCol] = PLAYER_MOVE;
        }
        else
        {
            // 如果没有找到最佳进攻位置，则随机选择一个空位下棋
            for (short i = 0; i < BOARD_SIZE; i++)
            {
                for (short j = 0; j < BOARD_SIZE; j++)
                {
                    if (grid[i][j] == 0)
                    {
                        std::cout << i << ' ' << j << std::endl;
                        grid[i][j] = PLAYER_MOVE;
                        goto end;
                    }
                }
            }
        }

    end:
        if (isGameOver(PLAYER_MOVE))
        {
            // 处理游戏结束逻辑
            break;
        }

        turnID++;
    }

    return 0;
}

bool isGameOver(short player)
{
    // 检查是否有五子连珠，即获胜
    for (short i = 0; i < BOARD_SIZE; i++)
    {
        for (short j = 0; j < BOARD_SIZE; j++)
        {
            if (isWinningMove(player, i, j))
            {
                return true;
            }
        }
    }
    return false;
}

bool isWinningMove(short player, short row, short col)
{
    // 判断在(row, col)位置下棋后是否形成了五子连珠

    // 水平方向
    short count = 1;
    for (short d = 1; d < BOARD_SIZE && col + d < BOARD_SIZE && grid[row][col + d] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }
    for (short d = 1; d < BOARD_SIZE && col - d >= 0 && grid[row][col - d] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }

    // 垂直方向
    count = 1;
    for (short d = 1; d < BOARD_SIZE && row + d < BOARD_SIZE && grid[row + d][col] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }
    for (short d = 1; d < BOARD_SIZE && row - d >= 0 && grid[row - d][col] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }

    // 左上到右下方向
    count = 1;
    for (short d = 1; d < BOARD_SIZE && row + d < BOARD_SIZE && col + d < BOARD_SIZE && grid[row + d][col + d] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }
    for (short d = 1; d < BOARD_SIZE && row - d >= 0 && col - d >= 0 && grid[row - d][col - d] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }

    // 右上到左下方向
    count = 1;
    for (short d = 1; d < BOARD_SIZE && row - d >= 0 && col + d < BOARD_SIZE && grid[row - d][col + d] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }
    for (short d = 1; d < BOARD_SIZE && row + d < BOARD_SIZE && col - d >= 0 && grid[row + d][col - d] == player; d++)
    {
        count++;
        if (count == 5)
            return true;
    }

    return false;
}

bool isPotentialWinningMove(short player, short row, short col)
{
    // 判断在(row, col)位置下棋后是否形成了潜在的胜利路径

    // 水平方向
    short count = 0;
    for (short d = 1; d <= 4; d++)
    {
        if (col + d < BOARD_SIZE && (grid[row][col + d] == player || grid[row][col + d] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }
    for (short d = 1; d <= 4; d++)
    {
        if (col - d >= 0 && (grid[row][col - d] == player || grid[row][col - d] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }

    // 垂直方向
    count = 0;
    for (short d = 1; d <= 4; d++)
    {
        if (row + d < BOARD_SIZE && (grid[row + d][col] == player || grid[row + d][col] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }
    for (short d = 1; d <= 4; d++)
    {
        if (row - d >= 0 && (grid[row - d][col] == player || grid[row - d][col] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }

    // 左上到右下方向
    count = 0;
    for (short d = 1; d <= 4; d++)
    {
        if (row + d < BOARD_SIZE && col + d < BOARD_SIZE && (grid[row + d][col + d] == player || grid[row + d][col + d] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }
    for (short d = 1; d <= 4; d++)
    {
        if (row - d >= 0 && col - d >= 0 && (grid[row - d][col - d] == player || grid[row - d][col - d] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }

    // 右上到左下方向
    count = 0;
    for (short d = 1; d <= 4; d++)
    {
        if (row - d >= 0 && col + d < BOARD_SIZE && (grid[row - d][col + d] == player || grid[row - d][col + d] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }
    for (short d = 1; d <= 4; d++)
    {
        if (row + d < BOARD_SIZE && col - d >= 0 && (grid[row + d][col - d] == player || grid[row + d][col - d] == 0))
        {
            count++;
            if (count == 4)
                return true;
        }
        else
        {
            break;
        }
    }

    return false;
}

short calculateMoveScore(short row, short col)
{
    // 根据棋局状态评估选择该位置的得分

    short score = 0;

    // 计算当前位置的得分
    score += calculateLineScore(row, col, 0, 1);  // 水平方向得分
    score += calculateLineScore(row, col, 1, 0);  // 垂直方向得分
    score += calculateLineScore(row, col, 1, 1);  // 左上到右下方向得分
    score += calculateLineScore(row, col, -1, 1); // 右上到左下方向得分

    return score;
}

short calculateLineScore(short row, short col, short dRow, short dCol)
{
    // 计算某个方向上的得分

    short score = 0;
    short player = PLAYER_MOVE;

    // 向前遍历，计算连续的棋子数量
    short count = 0;
    for (short i = 1; i <= 4; i++)
    {
        short r = row + i * dRow;
        short c = col + i * dCol;
        if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE)
        {
            if (grid[r][c] == player)
            {
                count++;
            }
            else if (grid[r][c] == -player)
            {
                count = 0;
                break;
            }
        }
        else
        {
            break;
        }
    }

    // 根据连子数量赋予得分
    if (count == 1)
    {
        score += TWO_COUNT_SCORE;
    }
    else if (count == 2)
    {
        score += THREE_COUNT_SCORE;
    }
    else if (count == 3)
    {
        score += FOUR_COUNT_SCORE;
    }
    else if (count == 4)
    {
        score += PLAYER_WIN_SCORE;
    }

    return score;
}
