#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

// KMP template
class KMP
{
    string b;

public:
    vector<int> nx;

    KMP(string b)
    {
        this->b = b;
        int n = b.length();
        int j = 0;
        nx.resize(n);
        for (int i = 1; i < n; i++)
        {
            while (j > 0 && b[i] != b[j])
                j = nx[j - 1];
            if (b[i] == b[j])
                j++;
            nx[i] = j;
        }
    }
    int matchTimes(string a) // a中出现多少次b
    {
        int n = b.length(), m = a.length();
        int j = 0;
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            while (j > 0 && a[i] != b[j])
                j = nx[j - 1];
            if (a[i] == b[j])
                j++;
            if (j == n)
            {
                ans++;
                j = nx[j - 1];
            }
        }
        return ans;
    }
    int firstMatchLocation(string a) // b在a中第一次出现的位置下标
    {
        int n = b.length(), m = a.length();
        int j = 0;
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            while (j > 0 && a[i] != b[j])
                j = nx[j - 1];
            if (a[i] == b[j])
                j++;
            if (j == n)
            {
                return i - n + 1;
            }
        }
        return -1;
    }
};

//

// const int N = 1e6 + 10;
// int Next[N];
// char a[N];
// int Size; //= strlen(a + 1);需要在主函数中计算 从1开始，需scanf("%s",a+1);

// void cal_next(char a[], int Size) // 求出next数组
// {
//     Next[1] = 0;
//     for (int i = 2, j = 0; i <= Size; i++)
//     {
//         while (j && a[i] != a[j + 1])
//             j = Next[j];
//         if (a[i] == a[j + 1])
//             j++;
//         Next[i] = j;
//     }
// }

// //

// // 下标从0开始
// #include <bits/stdc++.h>
// using namespace std;
// const int MAXN = 1e4 + 5;
// const int MAXM = 1e5 + 5;
// int Next[MAXN];
// void Get_Next(string sub, int len)
// {
//     int i = 0, j = -1;
//     Next[0] = -1;
//     while (i < len)
//     {
//         if (~j && sub[i] != sub[j])
//             j = Next[j];
//         else
//             Next[++i] = ++j;
//     }
// }
// int KMP(string s, int lena, string sub, int lenb)
// {
//     Get_Next(sub, lenb);
//     int i = 0, j = 0;
//     while (i < lena)
//     {
//         if (~j && s[i] != sub[j])
//             j = Next[j];
//         else
//             i++, j++;
//         if (j >= lenb)
//         {
//             j = Next[j];
//             return i - lenb;
//         }
//     }
//     return -1;
// }

// //

// // 下标从1开始
// #include <iostream>
// #include <cstdio>
// using namespace std;
// const int N = 1e5 + 10, M = 1e6 + 10;
// int n, m;
// int ne[N]; // next数组,next[i]表示子串s[1,2,,,,,,i-1,i]的最长相等前后缀的前缀最后一位下标
// // 或者说是子串的最长相等前后缀的长度，因为我们是从下标1开始的，这也体现出了从1开始的好处
// char s[M]; // 原字符串
// char p[N]; // 模板串
// int main()
// {
//     for (int i = 2, j = 0; i <= n; i++) // 求next数组 next[1]=0,因此从2开始
//     {
//         while (j && p[i] != p[j + 1])
//             j = ne[j]; // p[i] != p[j + 1]匹配失败,j回退
//         if (p[i] == p[j + 1])
//             j++; // 匹配成功，ne[i]=j+1,先令j指向这个位置
//         ne[i] = j;
//     }
//     for (int i = 1, j = 0; i <= m; i++) // 由于s[i]和p[j+1]匹配,因此j要往前错一位从0开始
//     {
//         while (j && s[i] != p[j + 1])
//             j = ne[j]; // 此时next数组的含义就是当j+1位失配时，j应该退回的位置
//         if (s[i] == p[j + 1])
//             j++;    // 匹配成功，j++指向下一个位置
//         if (j == n) // 匹配到模板串尽头，输出位置
//         {
//             printf("%d ", i - n);
//             j = ne[j]; // 让j回退到next[j]继续下一次匹配
//         }
//     }
//     return 0;
// }