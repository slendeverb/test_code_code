#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 610;
int a[N];

int gcd(int a, int b)
{
    int t;
    while (t = a % b)
    {
        a = b;
        b = t;
    }
    return b;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        if (n == 0)
        {
            break;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        sort(a, a + n);
        int ans = 0;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (gcd(a[i], a[j]) == 1)
                {
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}