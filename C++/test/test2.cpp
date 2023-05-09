#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void EgyptianFraction(int p, int q, vector<pair<int, int>> &res)
{
    if (p == 0 || q == 0)
        return;

    if (q % p == 0)
    {
        res.push_back(make_pair(1, q / p));
        return;
    }

    if (p % q == 0)
    {
        res.push_back(make_pair(p / q, 1));
        return;
    }

    int n = q / p + 1;
    res.push_back(make_pair(1, n));
    EgyptianFraction(p * n - q, q * n, res);
}

int main()
{
    int p, q;
    while (cin >> p >> q)
    {
        vector<pair<int, int>> res;
        EgyptianFraction(p, q, res);

        bool isValid = true;
        for (const auto &item : res)
        {
            if (item.second > 1000000 || item.second == q)
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
                    cout << "+";
                cout << "1/" << res[i].second;
            }
            cout << "\n";
        }
    }
    return 0;
}
