#include <iostream>
using namespace std;

const int N = 1e5 + 5;
int a[N];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        long long sum = 0;
        long long num1 = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            sum += a[i];
            if (a[i] == 1)
            {
                num1++;
            }
        }
        if (n == 1)
        {
            cout << "NO\n";
        }
        else if (sum - num1 - (n - num1) >= num1)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
    return 0;
}