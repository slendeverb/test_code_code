#include <iostream>
using namespace std;

const int N = 1e6 + 5;
int a[31], b[N], xor_sum[N];
int n, k;

void solve()
{
    cin >> n >> k;
    for (int i = 1; i <= 30; i++)
    {
        a[i] = -1;
    }
    xor_sum[0] = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        cin >> b[i];
        xor_sum[i] = xor_sum[i - 1] ^ b[i];
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int t = 31;
        if (b[i] == 0)
        {
            continue;
        }
        while (((b[i] >> (--t)) & 1) == 0)
        {
            ;
        }
        int x = 1;
        if ((xor_sum[i] >> t) & 1)
        {
            x = 0;
        }
        if (a[t + 1] != -1 && a[t + 1] != x)
        {
            cout << "-1\n";
            return;
        }
        else
        {
            a[t + 1] = x;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= 30; i++)
    {
        if (a[i] == -1)
        {
            cnt++;
        }
    }
    if (k > (1 << cnt))
    {
        cout << "-1\n";
        return;
    }
    else
    {
        k--;
        int p = 0;
        while (k)
        {
            while (a[++p] != -1)
            {
                ;
            }
            a[p] = k & 1;
            k >>= 1;
        }
    }
    for (int i = 1; i <= 30; i++)
    {
        if (a[i] == -1)
        {
            a[i] = 0;
        }
    }
    int x = 0;
    for (int i = 30; i >= 1; --i)
    {
        x = x * 2 + a[i];
    }
    cout << x;
    for (int i = 1; i <= n - 1; i++)
    {
        cout << " " << (x ^= b[i]);
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}