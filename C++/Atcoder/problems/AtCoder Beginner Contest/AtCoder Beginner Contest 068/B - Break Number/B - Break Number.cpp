#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    /*int ans = 0;
    int max = 0;
    for (int i = n % 2 == 0 ? n : n - 1; i >= 1; i -= 2)
    {
        int count = 0;
        int x = i;
        while (x % 2 == 0)
        {
            count++;
            x /= 2;
        }
        if (max < count)
        {
            max = count;
            ans = i;
        }
    }
    if (n == 1)
    {
        cout << 1 << endl;
    }
    else
    {
        cout << ans << endl;
    }*/
    int ans = 0;
    for (int i = 1; i <= n; i *= 2)
    {
        ans = i;
    }
    cout << ans << endl;
    return 0;
}