#include <iostream>
using namespace std;

const int N = 110;
int n, m;
int root[N];

void initset()
{
    for (int i = 0; i <= n; i++)
    {
        root[i] = i;
    }
}

int find(int x)
{
    return x == root[x] ? x : root[x] = find(root[x]);
}

void merge(int x, int y)
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
    cin >> n >> m;
    initset();
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        merge(a, b);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (find(i) == i)
        {
            cnt++;
        }
    }
    cout << cnt << "\n";
    return 0;
}