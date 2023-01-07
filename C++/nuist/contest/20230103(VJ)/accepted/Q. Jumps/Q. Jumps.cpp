#include <iostream>
using namespace std;

// 先求出sum的区间
// 只有sum-1需要多一步
// 其它的如sum -2,-3.....-n都可以通过不加n-1反而-1(相当于-n)来实现

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int x;
        cin >> x;
        int ans = 0, sum = 0;
        for (int i = 1; i <= x; i++)
        {
            sum += i;
            if (sum >= x)
            {
                ans = i;
                break;
            }
        }
        if (sum == x + 1)
        {
            cout << ans + 1 << "\n";
        }
        else
        {
            cout << ans << "\n";
        }
    }
    return 0;
}