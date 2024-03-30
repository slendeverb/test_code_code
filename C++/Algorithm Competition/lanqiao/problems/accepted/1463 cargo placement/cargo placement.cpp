#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;

int main()
{
    long long n = 2021041820210418L;
    vector<LL> v;

    for (LL i = 1; i * i <= n; i++)
        if (n % i == 0)
        {
            v.push_back(i);
            if (n / i != i)
            {
                v.push_back(n / i);
            }
        }

    LL ans = 0;
    for (auto i : v)
        for (auto j : v)
            for (auto k : v)
                if (i * j * k == n)
                    ans++;

    cout << ans << '\n';
    return 0;
}