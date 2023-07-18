#include <bits\stdc++.h>
typedef int int_32;
#define int long long
using namespace std;
int_32 main(void)
{
    int t;
    cin >> t;
    while (t--)
    {
        //信息维护，制造两个变量存储信息，一个flag表示是否找到需要的字符，找到后flag成为存储位置信息的容器
        //另一个变量ans，负责更新答案
        int n;
        char a;
        string s;
        cin >> n >> a >> s;
        // a为绿色，无需判断
        if (a == 'g')
        {
            cout << 0 << endl;
            continue;
        }
        s = s + s;
        int flag_pos = -1;
        int ans = -1;
        for (int i = 0; i < 2 * n; i++)
        {
            if (s[i] == a && flag_pos == -1)
                flag_pos = i;
            if (s[i] == 'g' && flag_pos != -1)
            {
                ans = max(ans, i - flag_pos);
                flag_pos = -1;
                if (i > n)
                    break;
            }
        }
        cout << ans << endl;
    }
}