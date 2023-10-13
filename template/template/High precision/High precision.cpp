// 压位高精度

#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define max(a, b) ((a) > (b)) ? (a) : (b)
#define min(a, b) ((a) < (b)) ? (a) : (b)
#define p 8             // 要压的位数
#define carry 100000000 // 相应的10的P次方 用于进位

const LL MAXN = 3005;
const string scarry = "100000000";

struct bigNum
{
private:
    LL t[MAXN], siz;

public:
    bigNum(string s)
    {
        memset(t, 0, sizeof(t));
        siz = 0;
        LL len = s.size();
        string tmp;
        tmp.resize(p);
        while (len >= p)
        {
            for (LL i = 0; i < p; ++i)
            {
                tmp[i] = s[len - p + i];
            }
            ++siz;
            for (LL i = 0; i < tmp.size(); ++i)
            {
                t[siz] += tmp[i] - '0';
                if (i < tmp.size() - 1)
                {
                    t[siz] *= 10;
                }
            }
            len -= p;
        }
        if (len)
        {
            tmp = "";
            tmp.resize(len);
            for (LL i = 0; i < len; ++i)
            {
                tmp[i] = s[i];
            }
            ++siz;
            for (LL i = 0; i < tmp.size(); ++i)
            {
                t[siz] += tmp[i] - '0';
                if (i < tmp.size() - 1)
                {
                    t[siz] *= 10;
                }
            }
        }
    }

    bigNum(void)
    {
        memset(t, 0, sizeof(t));
        siz = 1;
        return;
    }

    bigNum(LL x)
    {
        memset(t, 0, sizeof(t));
        char tmp[3005];
        siz = 0;
        while (x)
        {
            tmp[++siz] = x % 10 + '0';
            x /= 10;
        }

        *this = (string)tmp;
        return;
    }

    void print(void)
    {
        printf("%d", t[siz]);
        for (LL i = siz - 1; i >= 1; --i)
        {
            char tmp[] = "%00d";
            tmp[2] = p + '0';
            printf(tmp, t[i]);
        }
        putchar('\n');
    }

    LL size(void)
    {
        return siz;
    }

    friend bigNum operator-(bigNum a, bigNum b)
    {
        if (a == b)
            return (bigNum)0;
        if (a < b)
            swap(a, b);
        bigNum c;
        LL jw = 0;
        LL len = max(a.size(), b.size());
        for (LL i = 1; i <= len; ++i)
        {
            c.t[i] = a.t[i] - b.t[i] - jw;
            if (c.t[i] < 0)
            {
                jw = 1;
                c.t[i] += carry;
            }
            else
                jw = 0;
        }
        while (c.t[len] == 0)
        {
            --len;
        }
        c.siz = len;
        return c;
    }

    friend bigNum operator+(bigNum a, bigNum b)
    {
        bigNum c;
        LL jw = 0;
        LL len = max(a.size(), b.size());
        for (LL i = 1; i <= len; ++i)
        {
            c.t[i] = a.t[i] + b.t[i] + jw;
            if (c.t[i] >= carry)
            {
                jw = 1;
                c.t[i] -= carry;
            }
            else
                jw = 0;
        }
        if (jw)
        {
            c.t[++len] = 1;
        }
        c.siz = len;
        return c;
    }

    friend bigNum operator*(bigNum a, bigNum b)
    {
        bigNum c;
        LL len = a.siz + b.siz;
        for (LL i = 1; i <= a.siz; i++)
        {
            for (LL j = 1; j <= b.siz; j++)
            {
                c.t[i + j - 1] += a.t[i] * b.t[j];
                c.t[i + j] += c.t[i + j - 1] / carry;
                c.t[i + j - 1] %= carry;
            }
        }
        while (len > 0 && c.t[len] == 0)
            len--;
        c.siz = len;
        return c;
    }

    friend bigNum operator/(bigNum a, int b)
    {
        bigNum c;
        LL g = 0;
        for (int i = a.siz; i > 0; --i)
        {
            g = g * carry + a.t[i];
            c.t[i] = g / b;
            g %= b;
        }
        c.siz = a.siz;
        while (c.siz > 1 && c.t[c.siz] == 0)
            c.siz--;
        return c;
    }

    friend bool operator==(bigNum a, bigNum b)
    {
        if (a.siz != b.siz)
        {
            return 0;
        }
        for (LL i = 1; i <= a.siz; ++i)
        {
            if (a.t[i] != b.t[i])
            {
                return 0;
            }
        }
        return 1;
    }

    friend bool operator<(bigNum a, bigNum b)
    {
        if (a.siz != b.siz)
        {
            return a.siz < b.siz;
        }
        for (LL i = a.siz; i >= 1; --i)
        {
            if (a.t[i] < b.t[i])
            {
                return 1;
            }
            if (a.t[i] > b.t[i])
            {
                return 0;
            }
        }
        return 0;
    }

    friend bool operator<=(bigNum a, bigNum b)
    {
        return !(a > b);
    }

    friend bool operator>(bigNum a, bigNum b)
    {
        if (a.siz != b.siz)
        {
            return a.size() > b.size();
        }
        for (LL i = a.size(); i >= 1; --i)
        {
            if (a.t[i] > b.t[i])
            {
                return 1;
            }
            if (a.t[i] < b.t[i])
            {
                return 0;
            }
        }
        return 0;
    }

    friend bool operator>=(bigNum a, bigNum b)
    {
        return !(a < b);
    }
};

//

// 高精度除以高精度

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int L = 110;
int sub(int *a, int *b, int La, int Lb)
{
    if (La < Lb)
        return -1; // 如果a小于b，则返回-1
    if (La == Lb)
    {
        for (int i = La - 1; i >= 0; i--)
            if (a[i] > b[i])
                break;
            else if (a[i] < b[i])
                return -1; // 如果a小于b，则返回-1
    }
    for (int i = 0; i < La; i++) // 高精度减法
    {
        a[i] -= b[i];
        if (a[i] < 0)
            a[i] += 10, a[i + 1]--;
    }
    for (int i = La - 1; i >= 0; i--)
        if (a[i])
            return i + 1; // 返回差的位数
    return 0;             // 返回差的位数
}
string div(string n1, string n2, int nn) // n1,n2是字符串表示的被除数，除数,nn是选择返回商还是余数
{
    string s, v;                                                      // s存商,v存余数
    int a[L], b[L], r[L], La = n1.size(), Lb = n2.size(), i, tp = La; // a，b是整形数组表示被除数，除数，tp保存被除数的长度
    fill(a, a + L, 0);
    fill(b, b + L, 0);
    fill(r, r + L, 0); // 数组元素都置为0
    for (i = La - 1; i >= 0; i--)
        a[La - 1 - i] = n1[i] - '0';
    for (i = Lb - 1; i >= 0; i--)
        b[Lb - 1 - i] = n2[i] - '0';
    if (La < Lb || (La == Lb && n1 < n2))
    {
        // cout<<0<<endl;
        return n1;
    }                                 // 如果a<b,则商为0，余数为被除数
    int t = La - Lb;                  // 除被数和除数的位数之差
    for (int i = La - 1; i >= 0; i--) // 将除数扩大10^t倍
        if (i >= t)
            b[i] = b[i - t];
        else
            b[i] = 0;
    Lb = La;
    for (int j = 0; j <= t; j++)
    {
        int temp;
        while ((temp = sub(a, b + j, La, Lb - j)) >= 0) // 如果被除数比除数大继续减
        {
            La = temp;
            r[t - j]++;
        }
    }
    for (i = 0; i < L - 10; i++)
        r[i + 1] += r[i] / 10, r[i] %= 10; // 统一处理进位
    while (!r[i])
        i--; // 将整形数组表示的商转化成字符串表示的
    while (i >= 0)
        s += r[i--] + '0';
    // cout<<s<<endl;
    i = tp;
    while (!a[i])
        i--; // 将整形数组表示的余数转化成字符串表示的</span>
    while (i >= 0)
        v += a[i--] + '0';
    if (v.empty())
        v = "0";
    // cout<<v<<endl;
    if (nn == 1)
        return s;
    if (nn == 2)
        return v;
}