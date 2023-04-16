#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e6 + 10;
int ans[maxn];
const int mod = 998244353;

int main()
{
    int t;
    cin >> t;
    ans[1] = 1;
    ans[2] = 2;
    ans[3] = 3;
    for (int i = 4; i <= 1000000; i++)
    {
        ans[i] = (ans[i - 1] + ans[i - 2]) % mod;
    }
    while (t--)
    {
        int n;
        cin >> n;
        cout << ans[n] << "\n";
    }
    return 0;
}