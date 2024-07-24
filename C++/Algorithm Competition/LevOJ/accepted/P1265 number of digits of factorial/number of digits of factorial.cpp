#include <iostream>
#include <cmath>
using namespace std;

int n, num;

int main()
{
    cin >> n;
    while (n--)
    {
        double ans = 0;
        cin >> num;
        for (int i = num; i >= 1; i--)
        {
            ans += log10(i);
        }
        cout << ceil(ans) << "\n";
    }
    return 0;
}