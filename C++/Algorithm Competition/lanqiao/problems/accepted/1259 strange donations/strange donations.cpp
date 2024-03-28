#include <iostream>
#include <vector>
using namespace std;

void solve()
{
    int x = 1000000;
    int maxCount = 0;
    while (x)
    {
        maxCount += (x % 7);
        x /= 7;
    }
    std::cout << maxCount << std::endl;
}

int main()
{
    solve();
    return 0;
}