#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int width = 310;
bool board[width][width];
const int step[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {-1, 2}, {-2, 1}, {2, -1}, {1, 2}, {2, 1}};
typedef struct knight
{
    int x;
    int y;
    int step;
} knight;

bool inboard(knight k)
{
    if (k.x >= 0 && k.x < width && k.y >= 0 && k.y < width)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void bfs(int x1, int y1, int x2, int y2, int L)
{
    queue<knight> q;
    knight begin, pos, next;
    begin.x = x1, begin.y = y1;
    begin.step = 0;
    board[begin.x][begin.y] = true;
    q.push(begin);
    while (!q.empty())
    {
        pos = q.front();
        q.pop();
        if (pos.x == x2 && pos.y == y2)
        {
            cout << pos.step << "\n";
            return;
        }
        for (int i = 0; i < 8; i++)
        {
            next.x = pos.x + step[i][0];
            next.y = pos.y + step[i][1];
            if (inboard(next) && board[next.x][next.y] != true)
            {
                next.step = pos.step + 1;
                board[next.x][next.y] = true;
                q.push(next);
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int L;
        cin >> L;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        memset(board, 0, sizeof(board));
        bfs(x1, y1, x2, y2, L);
    }
    return 0;
}