#include <iostream>
#include <string>
using namespace std;

string divide_by_2(const string &num_str)
{
    string result;
    int carry = 0;
    for (int i = 0; i < num_str.size(); i++)
    {
        char digit = num_str[i];
        int current = carry * 10 + (digit - '0');
        carry = current % 2;
        result += (current / 2) + '0';
    }

    // 去除结果中的前导零
    size_t pos = result.find_first_not_of('0');
    if (pos != string::npos)
    {
        result = result.substr(pos);
    }
    else
    {
        result = "0";
    }

    return result;
}

int qpow(int a, string &b, int mod)
{
    int res = 1;
    a = (a % mod + mod) % mod;
    while (b != "0")
    {
        if ((b.back() - '0') % 2)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b = divide_by_2(b);
    }
    return res;
}

int main()
{
    int a;
    string b;
    while (cin >> a >> b)
    {
        cout << qpow(a, b, 1337) << "\n";
    }
    return 0;
}