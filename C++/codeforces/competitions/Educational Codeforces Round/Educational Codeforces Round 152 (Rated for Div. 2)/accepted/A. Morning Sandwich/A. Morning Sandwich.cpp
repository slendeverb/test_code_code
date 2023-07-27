#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int b, c, h;
        cin >> b >> c >> h;
        long long ans = 0;
        if (c + h > b - 1)
        {
            ans = b + b - 1;
        }
        else
        {
            ans = c + h + c + h + 1;
        }
        cout << ans << "\n";
    }
    return 0;
}