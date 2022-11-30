#include <iostream>
#include <cstring>
using namespace std;

//

const int N = 1e6 + 10;
int Next[N];
char a[N];
int n; //= strlen(a + 1);需要在主函数中计算 //从1开始，需cin>>a+1;
int maxx;

void cal_next(char a[], int n) //求出next数组
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