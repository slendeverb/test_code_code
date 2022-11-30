#include <iostream>
using namespace std;

int n, m, p;

const int N = 3e5 + 10;
int root[N]; //记录根节点

void initset()
{
    for (int i = 0; i <= n; i++)
    {
        root[i] = i;
    }
}

int find(int x)
{
    return x == root[x] ? x : root[x] = find(root[x]); //路径压缩
}

void merge1(int x, int y)
{
    int dx = find(x);
    int dy = find(y);
    if (dx != dy)
    {
        root[dy] = dx;
    }
}

int main()
{
    cin >> n >> m >> p;
    initset();
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        merge1(x, y);
    }
    for (int i = 0; i < p; i++)
    {
        int x, y;
        cin >> x >> y;
        if (find(x) == find(y))
        {
            cout << "Yes"
                 << "\n";
        }
        else
        {
            cout << "No"
                 << "\n";
        }
    }
    return 0;
}