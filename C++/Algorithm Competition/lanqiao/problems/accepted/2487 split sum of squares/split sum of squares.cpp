#include <iostream>
#include <vector>
#include <set>
using namespace std;

void solve()
{
    std::vector<int> xpow2;
    for (int i = 0; i * i <= 2021; i++)
    {
        xpow2.push_back(i * i);
    }
    std::set<int> squareSumNumber;
    for (int i = 0; i < xpow2.size(); i++)
    {
        for (int j = 0; j < xpow2.size(); j++)
        {
            int sum = xpow2[i] + xpow2[j];
            if (sum >= 1 && sum <= 2021)
            {
                squareSumNumber.insert(sum);
            }
        }
    }

    std::cout << squareSumNumber.size() << std::endl;
}

int main()
{
    solve();
    return 0;
}