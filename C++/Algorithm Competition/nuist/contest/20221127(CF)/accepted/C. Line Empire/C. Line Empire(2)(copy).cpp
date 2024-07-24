//正确思路：需要考虑的是从哪个点出发去攻占一个待攻占的点，转移起点会花费a*|c2-c1|,
//需要判断花费值不值，若后面还有m个待攻占的点，此时存在关系a*|c2-c1|<=|c2-c1|*m*b，则表明将起点转移到c2是值得的

#include <stdio.h>

typedef long long ll;
const int N = 2e5 + 10;
ll s[N];
int n, a, b, k;

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {

        scanf("%d %d %d", &n, &a, &b);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &s[i]);
        ll res = 0;
        int l = 0;
        for (int i = 1; i <= n; i++)
        {
            res += b * (s[i] - s[l]);
            if ((s[i] - s[l]) * a <= (s[i] - s[l]) * b * 1ll * (n - i))
            {
                res += a * (s[i] - s[l]);
                l = i;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
