#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
const long long p = 31;

vector<string> v;

long long Hash[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            string tmp;
            cin >> tmp;
            string s = " " + tmp + tmp;
            int I = 1, J = 2;
            while (J <= m) // 寻找字符串的最小表示法,最后I为字符串最小开头
            {
                for (int k = 0; k < m; k++)
                {
                    if (s[I + k] < s[J + k])
                    {
                        J += k;
                        break;
                    }
                    if (s[I + k] > s[J + k])
                    {
                        int tmpI = I;
                        I = J;
                        J = max(J, tmpI + k);
                        break;
                    }
                }
                J++;
            }
            Hash[i] = 0;
            for (int j = 0; j < m; j++)
            {
                Hash[i] = (Hash[i] * p + s[I + j] - 'a' + 1) % mod;
            }
        }
        int q;
        cin >> q;
        while (q--)
        {
            int x, y;
            cin >> x >> y;
            if (Hash[x] == Hash[y])
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
    }
    return 0;
}