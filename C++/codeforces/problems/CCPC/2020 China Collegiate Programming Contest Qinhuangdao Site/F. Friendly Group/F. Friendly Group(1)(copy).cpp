#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define llinf 0x3f3f3f3f3f3f3f3f
#define int long long
#define ull unsigned long long
#define PII pair<int, int>
using namespace std;
typedef long long LL;
const int N = 3e5 + 100;
const int mod = 1e9 + 7;
const double pi = acos(-1.0);
int t, n, m;
int root[N];
int road[N]; //同一集合通路数
int cnt[N];  //同一集合人数
int ans;
void init()
{ //初始化
    for (int i = 0; i <= n; i++)
    {
        root[i] = i; //初始以自己为根
        road[i] = 0; //初始没通路
        cnt[i] = 1;  //初始只有自己一个人
    }
    return;
}
int find(int x) { return x == root[x] ? x : root[x] = find(root[x]); } //路径压缩
void merge(int x, int y)
{
    int dx = find(x);
    int dy = find(y);
    if (dx != dy)
    {                         //不同根
        cnt[dx] += cnt[dy];   //集合人数叠加
        road[dx] += road[dy]; //集合通路数叠加
                              //并根在增加操作之后
        root[dy] = dx;
        road[dx]++; //并根时增加的一条通路
    }
    else
    { //同根，只有通路数增加
        road[dx]++;
    }
    return;
}
void solve()
{
    init();
    int x, y;
    while (m--)
    { //加边操作
        cin >> x >> y;
        if (y < x)
            swap(x, y); //这里我默认前面比后面的序号大，不知道对merge有没有影响
        merge(x, y);
    }
    ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (root[i] == i)
        {
            int t = road[i] - cnt[i];
            if (t >= 0)
                ans += t; //如果贡献为正就相加
        }
    }
    return;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        cin >> n >> m;
        solve();
        cout << "Case #" << i << ": " << ans << endl; //输出
    }
    return 0;
}
/*
    i raised a cute kitty in my code,
    my friend who pass by can touch softly on her head:)

         ／l、
   Meow~（ﾟ､ 。７
         |、 ~ヽ
         じしf_,)ノ

*/
