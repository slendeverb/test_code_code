#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void EgyptianFraction(unsigned long long p, unsigned long long q, vector<unsigned long long> &res)
{
    if (p == 0 || q == 0)
    {
        return;
    }

    if (q % p == 0)
    {
        res.push_back(q / p);
        return;
    }

    if (p % q == 0)
    {
        res.push_back(p / q);
        return;
    }

    unsigned long long n = ceil((double)q / p);
    res.push_back(n);

    unsigned long long new_p = p * n - q;
    unsigned long long new_q = q * n;
    unsigned long long g = gcd(new_p, new_q);

    EgyptianFraction(new_p / g, new_q / g, res);
}

int main()
{
    int p, q;
    while (cin >> p >> q)
    {
        vector<unsigned long long> res;
        EgyptianFraction(p, q, res);

        bool isValid = true;
        for (const auto &item : res)
        {
            if (item > 1000000 || item == q || item <= 0)
            {
                isValid = false;
                break;
            }
        }

        if (!isValid)
        {
            cout << "No found!\n";
        }
        else
        {
            for (size_t i = 0; i < res.size(); ++i)
            {
                if (i > 0)
                {
                    cout << "+";
                }
                cout << "1/" << res[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
