#include <iostream>
#include <cstring>
using namespace std;

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

int main()
{
    cin >> a + 1;
    n = strlen(a + 1);
    cal_next(a, n);
    int x = Next[n];
    if (x == 0)
    {
        cout << "Just a legend"
             << "\n";
    }
    else
    {
        while (x > maxx)
        {
            x = Next[x];
        }
        if (x == 0)
        {
            cout << "Just a legend"
                 << "\n";
        }
        else
        {
            for (int i = 2; i <= n - 1; i++)
            {
                if (Next[i] == x)
                {
                    for (int j = i - Next[i] + 1; j <= i; j++)
                    {
                        cout << a[j];
                    }
                    cout << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}