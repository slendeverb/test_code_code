#include <iostream>
using namespace std;

const int maxn = 60;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int a, b, ans = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a >> b;
            if (a > b)
            {
                ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}