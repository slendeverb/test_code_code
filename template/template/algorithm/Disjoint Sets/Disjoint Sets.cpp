#define int long long
int t, n, m;

//

const int N = 3e5 + 10;
int root[N]; // 记录根节点
int road[N]; // 记录同一集合通路
int cnt[N];  // 记录同一集合人数

void initset()
{
    for (int i = 0; i <= n; i++)
    {
        root[i] = i;
        road[i] = 0;
        cnt[i] = 0;
    }
}

int find(int x)
{
    return x == root[x] ? x : root[x] = find(root[x]); // 路径压缩
}

bool merge(int x, int y)
{
    int dx = find(x);
    int dy = find(y);
    if (dx != dy)
    {
        root[dy] = dx;
        return true;
    }
    return false;
}

void merge2(int x, int y)
{
    int dx = find(x);
    int dy = find(y);
    if (dx != dy) // 不同根
    {
        cnt[dx] += cnt[dy];   // 集合人数叠加
        road[dx] += road[dy]; // 集合通路数叠加

        root[dy] = dx; // 并根在增加操作之后
        road[dx]++;    // 并根时增加的一条通路
    }
    else
    {
        road[dx]++; // 同根，只有通路数增加
    }
}