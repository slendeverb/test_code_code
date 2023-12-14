#include <iostream>
#include <cmath>
using namespace std;

//1.n=1时，即A为质数时成立

//2.n=2时，可以分为两种情况：
//  1.和为偶数时，使用强哥猜。
//  2.和为奇数时，当且仅当和-2为质数时成立，因为奇数只能由一个奇数和一个偶数相加得到，而除了二以外的偶数都不是质数，所以只能是2+a，也就是a为质数时才成立，所以减去2：

//3.n>2时。此时就可以运用哥德巴赫猜想了，n=3时，只要和大于5，也就是和为6（2+2+2）时是最小的成立条件。以此类推，只要满足和大于等于2*n即可。

const int maxn = 1010;

int a[maxn];

bool isprime(int num)
{
    if (num == 2 || num == 3)
    {
        return true;
    }
    if (num % 6 != 1 || num % 6 != 5)
    {
        return false;
    }
    for (int i = 5; i <= sqrt(num); i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    if (n == 1)
    {
        if (isprime(sum))
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
    else if (n == 2)
    {
        if (sum % 2 != 0 && isprime(sum - 2))
        {
            cout << "Yes\n";
        }
        else if (sum % 2 == 0 && sum >= 4)
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
    else
    {
        if (sum % 2 == 1)
        {
            if (sum >= 2 * n + 1)
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
        else
        {
            if (sum >= 2 * n)
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