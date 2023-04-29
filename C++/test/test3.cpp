#include <iostream>
using namespace std;

const int mod = 998244353;
int n;
const int maxn = 2e5 + 10;
int a[maxn], b[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n - 1; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                b[i] = a[i];
            }
            for (int j = i + 1; j <= n; j++)
            {
                
            }
        }
    }
    return 0;
}