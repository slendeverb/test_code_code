#include <bits/stdc++.h>
using namespace std;

int a, b;

void solve()
{
    cin >> a >> b;
    if (a == b)
    {
        cout << "0\n";
        return;
    }
    else
    {
        int d = abs(a - b);
        int x = sqrt(d);
        if (x * x == d)
        {
            cout << "1\n";
            return;
        }
        else if (d & 1 || d % 4 == 0)
        {
            cout << "2\n";
            return;
        }
        else
        {
            for (int i = 1; i * i < d; i++)
            {
                int x = sqrt(d - i * i);
                if (x * x == d - i * i)
                {
                    cout << "2\n";
                    return;
                }
            }
            cout << "3\n";
            return;
        }
    }
}

signed main()
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