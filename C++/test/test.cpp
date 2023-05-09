#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//算法思路如下：

//首先，我们考虑将任意真分数表示成埃及分数的和，这是一种贪心策略，即每次选择分母最小的分数，直到分数和等于原分数为止。我们将分数 p/q 依次分解成 1/a1 + 1/a2 + ... + 1/an 的形式，其中 ai 是埃及分数，要求 ai 两两不同且不能等于 q/p。具体的求解方法如下：

//1. 如果 p > q，则将 p/q 分解成 1/n + (p*n-q)/(q*n)，其中 n = ceil(p/q)。
//2. 如果 p = q，则 p/q = 1/1。
//3. 如果 q % p = 0，则 p/q = 1/(q/p)。
//4. 否则，将 p/q 分解成 1/n + (p*n-q)/(q*n)，其中 n = q/p + 1。

//以上过程可以递归地进行，直到分数被分解成 1/x 的形式。

//在程序中，我们首先读入一个分数 p/q，然后不断进行上述过程，直到分数被分解成 1/x 的形式或输入结束。最后，将每次得到的埃及分数拼接成字符串输出即可。如果无法分解成埃及分数，或者分解出的某个埃及分数的分母大于 1000000，则输出 "No found!"。

// 将分数 p / q 分解成若干个埃及分数之和
string egyptian_fractions(int p, int q)
{
    if (p == 1)
    {
        return to_string(q) + "/" + to_string(q + 1);
    }
    int n = ceil(1.0 * q / p);
    string result = "1/" + to_string(n);
    int new_p = p * n - q;
    int new_q = q * n;
    string remain = egyptian_fractions(new_p, new_q);
    if (remain == "No found!" || stoi(remain.substr(0, remain.find('/'))) == n)
    {
        return remain;
    }
    else
    {
        return result + "+" + remain;
    }
}

int main()
{
    int p, q;
    while (cin >> p >> q)
    {
        if (p == 0)
        {
            break;
        }
        bool found = false;
        string result;
        for (int i = 2; i <= 1000000; i++)
        {
            if (i != q && i != p)
            {
                int tmp = p * i;
                if ((tmp % (i - q)) == 0)
                {
                    int n = tmp / (i - q);
                    if (n > 1)
                    {
                        found = true;
                        result += "1/" + to_string(n) + "+";
                        p = p * n - q;
                        q = q * n;
                        break;
                    }
                }
            }
        }
        if (!found)
        {
            result = egyptian_fractions(p, q);
            if (result == "No found!")
            {
                cout << result << endl;
            }
            else
            {
                cout << result.substr(0, result.size() - 1) << endl;
            }
        }
        else
        {
            while (p != 1)
            {
                result += egyptian_fractions(p, q) + "+";
                cin >> p >> q;
            }
            cout << result.substr(0, result.size() - 1) << endl;
        }
    }
    return 0;
}
