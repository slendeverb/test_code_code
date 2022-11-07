#include <cstdio>
#include <algorithm>
using namespace std;
int a[200010];
int main()
{
    int k, n, i, mx = -1;
    scanf("%d%d", &k, &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (i = 2; i <= n; i++)
        mx = max(mx, a[i] - a[i - 1]); //寻找两房最大间距
    mx = max(mx, k - a[n] + a[1]);     //第一个房子与最后一个房子的间距计算
    printf("%d\n", k - mx);            //答案=周长-寻找两房最大间距
    return 0;
}