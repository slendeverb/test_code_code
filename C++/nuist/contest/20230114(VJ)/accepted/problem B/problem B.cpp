#include <iostream>
using namespace std;

int main()
{
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int x, cnt = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> x;
            if (x % 2 == 1)
            {
                cnt++;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}