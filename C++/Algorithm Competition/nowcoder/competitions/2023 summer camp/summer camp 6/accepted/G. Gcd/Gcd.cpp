#include <iostream>
using namespace std;

// 由裴蜀定理, 两个正整数辗转相减只能得到他们最大公约数的倍数

long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T;
    cin >> T;
    int x, y, z;
    while (T--)
    {
        cin >> x >> y >> z;
        if (x && y && z == 0)
        {
            cout << "NO\n";
        }
        else if (x == 0 || y == 0)
        {
            if (z == x || z == y)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
        else
        {
            int tmp = gcd(x, y);
            if (z % tmp == 0)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
    return 0;
}