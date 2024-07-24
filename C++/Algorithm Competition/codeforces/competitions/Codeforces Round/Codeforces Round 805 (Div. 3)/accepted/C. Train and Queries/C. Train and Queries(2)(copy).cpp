// Problem: C. Train and Queries
// Contest: Codeforces - Codeforces Round #805 (Div. 3)
// URL: https://codeforces.ml/contest/1702/problem/C
// Memory Limit: 256 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <map>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        map<int, int> mi;
        map<int, int> ma;
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            if (mi[x] == 0) //用于保存所有点最左边的位置
                mi[x] = i;
            ma[x] = i; //用于保存所有点最右边的位置
        }
        for (int i = 1; i <= k; i++)
        {
            int l, r;
            cin >> l >> r;
            if (mi[r] == 0 || ma[l] == 0)
                puts("NO");
            else
            {
                if (ma[r] > mi[l]) //比较最右边的终点和最左边的起点
                    puts("YES");
                else
                    puts("NO");
            }
        }
    }
    return 0;
}