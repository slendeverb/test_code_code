//我们可以先找到既是S前缀又是S后缀的子串，用KMP求出next数组即可实现。
//之后我们只需从2枚举到n-1这样可以保证既不是前缀也不是后缀，如果next[i]=next[n]那么就找到了最大的子串。
//我们还需要预处理一下，在求next数组时记录下max{next[1~n-1]}，
//那么当next[n]>max时显然不能将next[n]作为最长子串的长度（这样就会无法找到，输出“Just a legend”），
//所以当x=next[n]>max时，令x=next[x]，直到x<=max，注意如果这时next[x]=0还是无解。

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char a[1000010];
int Next[1000010], n, maxx = 0;
void cal() //求出next数组
{
    Next[1] = 0;
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && a[i] != a[j + 1])
            j = Next[j];
        if (a[i] == a[j + 1])
            j++;
        Next[i] = j;
        if (i != n)
            maxx = max(Next[i], maxx);
        //找到next数组的最大值
    }
}
int main()
{
    cin >> a + 1;
    n = strlen(a + 1);
    cal();
    int x = Next[n];
    if (x == 0)
        printf("Just a legend\n");
    else
    {
        while (x > maxx)
            x = Next[x];
        //找到小于max{next[1~n-1]}的最大匹配长度
        if (x == 0)
        {
            printf("Just a legend\n");
            return 0;
        }
        for (int i = 2; i < n; i++)
            if (x == Next[i])
            {
                for (int j = i - Next[i] + 1; j <= i; j++)
                    // i-next[i]+1为答案子串的左端点
                    printf("%c", a[j]);
                printf("\n");
                return 0;
            }
    }
    return 0;
}
