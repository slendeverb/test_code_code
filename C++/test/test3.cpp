#include <bitset>
#include <iostream>
#define btst std::bitset
#define cn std::cin
#define ct std::cout
#define endl std::endl
#define board(i) 0 <= i &&i < SIZE
#define str std::string
const short SIZE = 15, whole = 225;
short D[3] = {-1, 0, 1}, Grid[SIZE][SIZE] = {};

bool isGameOver(short player);
bool isWinningMove(short player, short row, short col);
bool isPotentialWinningMove(short player, short row, short col);
short calculateMoveScore(short row, short col);

int main() {
  short turnID = 0;
  while (true) {
    int oi, oj;
    scanf("%d%d", &oi, &oj);
    if (oi != -1 && oj != -1)
      Grid[oi][oj] = -1;
    if (turnID == 0) {
      int i = 7, j = 7;
      if (Grid[7][7])
        j = 8;
      ct << i << ' ' << j << endl;
      Grid[i][j] = 1;
      turnID++;
      continue;
    }
    short bestMoveRow = -1, bestMoveCol = -1;
    short maxScore = -1;

    for (short i = 0; i < SIZE; i++) {
      for (short j = 0; j < SIZE; j++) {
        if (Grid[i][j] == 0) {
          // 防守策略：检查对手是否有潜在的胜利路径
          if (isPotentialWinningMove(-1, i, j)) {
            ct << i << ' ' << j << endl;
            Grid[i][j] = 1;
            goto ed;
          }

          // 进攻策略：检查自己是否有潜在的胜利路径
          if (isPotentialWinningMove(1, i, j)) {
            // 选择具有最高得分的进攻位置
            short score = calculateMoveScore(i, j);
            if (score > maxScore) {
              maxScore = score;
              bestMoveRow = i;
              bestMoveCol = j;
            }
          }
        }
      }
    }

    // 如果找到了最佳进攻位置，则选择该位置下棋
    if (bestMoveRow != -1 && bestMoveCol != -1) {
      ct << bestMoveRow << ' ' << bestMoveCol << endl;
      Grid[bestMoveRow][bestMoveCol] = 1;
    } else {
      // 如果没有找到最佳进攻位置，则随机选择一个空位下棋
      for (short i = 0; i < SIZE; i++) {
        for (short j = 0; j < SIZE; j++) {
          if (Grid[i][j] == 0) {
            ct << i << ' ' << j << endl;
            Grid[i][j] = 1;
            goto ed;
          }
        }
      }
    }

  ed:
    if (isGameOver(1)) {
      // 处理游戏结束逻辑
      break;
    }

    turnID++;
  }

  return 0;
}

bool isGameOver(short player) {
  // 检查是否有五子连珠，即获胜
  for (short i = 0; i < SIZE; i++) {
    for (short j = 0; j < SIZE; j++) {
      if (isWinningMove(player, i, j)) {
        return true;
      }
    }
  }
  return false;
}

bool isWinningMove(short player, short row, short col) {
  // 判断在(row, col)位置下棋后是否形成了五子连珠

  // 水平方向
  short count = 1;
  for (short c = col + 1; c < SIZE && Grid[row][c] == player; c++) {
    count++;
    if (count == 5)
      return true;
  }
  for (short c = col - 1; c >= 0 && Grid[row][c] == player; c--) {
    count++;
    if (count == 5)
      return true;
  }

  // 垂直方向
  count = 1;
  for (short r = row + 1; r < SIZE && Grid[r][col] == player; r++) {
    count++;
    if (count == 5)
      return true;
  }
  for (short r = row - 1; r >= 0 && Grid[r][col] == player; r--) {
    count++;
    if (count == 5)
      return true;
  }

  // 左上到右下方向
  count = 1;
  for (short r = row + 1, c = col + 1; r < SIZE && c < SIZE && Grid[r][c] == player; r++, c++) {
    count++;
    if (count == 5)
      return true;
  }
  for (short r = row - 1, c = col - 1; r >= 0 && c >= 0 && Grid[r][c] == player; r--, c--) {
    count++;
    if (count == 5)
      return true;
  }

  // 右上到左下方向
  count = 1;
  for (short r = row - 1, c = col + 1; r >= 0 && c < SIZE && Grid[r][c] == player; r--, c++) {
    count++;
    if (count == 5)
      return true;
  }
  for (short r = row + 1, c = col - 1; r < SIZE && c >= 0 && Grid[r][c] == player; r++, c--) {
    count++;
    if (count == 5)
      return true;
  }

  return false;
}

bool isPotentialWinningMove(short player, short row, short col) {
  // 判断在(row, col)位置下棋后是否形成了潜在的胜利路径

  // 水平方向
  short count = 0;
  for (short c = col + 1; c < SIZE && (Grid[row][c] == player || Grid[row][c] == 0); c++) {
    count++;
    if (count == 4)
      return true;
  }
  for (short c = col - 1; c >= 0 && (Grid[row][c] == player || Grid[row][c] == 0); c--) {
    count++;
    if (count == 4)
      return true;
  }

  // 垂直方向
  count = 0;
  for (short r = row + 1; r < SIZE && (Grid[r][col] == player || Grid[r][col] == 0); r++) {
    count++;
    if (count == 4)
      return true;
  }
  for (short r = row - 1; r >= 0 && (Grid[r][col] == player || Grid[r][col] == 0); r--) {
    count++;
    if (count == 4)
      return true;
  }

  // 左上到右下方向
  count = 0;
  for (short r = row + 1, c = col + 1; r < SIZE && c < SIZE && (Grid[r][c] == player || Grid[r][c] == 0); r++, c++) {
    count++;
    if (count == 4)
      return true;
  }
  for (short r = row - 1, c = col - 1; r >= 0 && c >= 0 && (Grid[r][c] == player || Grid[r][c] == 0); r--, c--) {
    count++;
    if (count == 4)
      return true;
  }

  // 右上到左下方向
  count = 0;
  for (short r = row - 1, c = col + 1; r >= 0 && c < SIZE && (Grid[r][c] == player || Grid[r][c] == 0); r--, c++) {
    count++;
    if (count == 4)
      return true;
  }
  for (short r = row + 1, c = col - 1; r < SIZE && c >= 0 && (Grid[r][c] == player || Grid[r][c] == 0); r++, c--) {
    count++;
    if (count == 4)
      return true;
  }

  return false;
}

short calculateMoveScore(short row, short col) {
  // 根据棋局状态评估选择该位置的得分

  // 这里只是一个简单的示例评估函数
  // 可以根据实际需要和五子棋规则来设计更复杂的评估函数

  short score = 0;

  // 计算当前位置的得分
  // 可以根据连子数量、棋局形势、棋子的位置等因素来赋予得分
  // 这里只给出一个简单的示例
  score += calculateLineScore(row, col, 0, 1);  // 水平方向得分
  score += calculateLineScore(row, col, 1, 0);  // 垂直方向得分
  score += calculateLineScore(row, col, 1, 1);  // 左上到右下方向得分
  score += calculateLineScore(row, col, -1, 1); // 右上到左下方向得分

  return score;
}

short calculateLineScore(short row, short col, short dRow, short dCol) {
  // 计算某个方向上的得分
  // 可以根据连子数量、棋局形势、棋子的位置等因素来赋予得分
  // 这里只给出一个简单的示例
  short score = 0;
  short player = 1; // 假设是玩家1的棋子

  // 向前遍历，计算连续的棋子数量
  short count = 0;
  for (short i = 1; i <= 4; i++) {
    short r = row + i * dRow;
    short c = col + i * dCol;
    if (board(r) && board(c)) {
      if (Grid[r][c] == player) {
        count++;
      } else if (Grid[r][c] == -player) {
        count = 0;
        break; // 对手的棋子，无法形成连续的自己的棋子
      }
    }
  }

  // 根据连子数量赋予得分
  if (count == 1) {
    score += 10;
  } else if (count == 2) {
    score += 100;
  } else if (count == 3) {
    score += 1000;
  } else if (count == 4) {
    score += 10000;
  }

  return score;
}
