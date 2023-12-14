#include <iostream>
using namespace std;

const int N = 55;
int a[N];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        int ans = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i] <= a[i + 1])
            {
                continue;
            }
            else
            {
                ans = max(ans, a[i]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}