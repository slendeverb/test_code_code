#include <iostream>
#include <vector>
using namespace std;

struct HeaviestAndLightestChocolate
{
    int heaviest{INT_MIN};
    int lightest{INT_MAX};

    HeaviestAndLightestChocolate(int heaviest = INT_MIN, int lightest = INT_MAX)
        : heaviest{heaviest}, lightest{lightest} {}
};
std::ostream &operator<<(std::ostream &out, const HeaviestAndLightestChocolate &choco)
{
    out << "最重的巧克力：" << choco.heaviest << ", "
        << "最轻的巧克力：" << choco.lightest << "\n";
    return out;
}

HeaviestAndLightestChocolate findOutChocolates(std::vector<int> &chocolates, int start, int end)
{
    int difference = end - start + 1;
    if (difference <= 2)
    {
        if (difference == 0)
        {
            return HeaviestAndLightestChocolate{};
        }
        else if (difference == 1)
        {
            int choco = chocolates[start];
            return HeaviestAndLightestChocolate{choco, choco};
        }
        else
        {
            int choco1 = chocolates[start];
            int choco2 = chocolates[end];
            return HeaviestAndLightestChocolate{std::max(choco1, choco2), std::min(choco1, choco2)};
        }
    }
    int mid = ((end - start) >> 1) + start;
    auto resultLeft = findOutChocolates(chocolates, start, mid);
    auto resultRight = findOutChocolates(chocolates, mid + 1, end);
    return HeaviestAndLightestChocolate{std::max(resultLeft.heaviest, resultRight.heaviest), std::min(resultLeft.lightest, resultRight.lightest)};
}

int main()
{
    std::vector<int> chocolates;
    int x = 0;
    while (std::cin >> x)
    {
        chocolates.push_back(x);
    }
    int start = 0;
    int end = chocolates.size() - 1;
    auto answer = findOutChocolates(chocolates, start, end);
    std::cout << answer << std::endl;
    return 0;
}