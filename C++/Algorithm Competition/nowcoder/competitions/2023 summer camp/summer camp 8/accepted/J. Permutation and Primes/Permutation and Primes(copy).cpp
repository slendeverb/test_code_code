#include <bits/stdc++.h>
using namespace std;

int n;

void solve()
{
    cin >> n;
    if (n == 2)
    {
        cout << "1 2\n";
    }
    else if (n == 3)
    {
        cout << "1 2 3\n";
    }
    else if (n == 4)
    {
        cout << "1 2 3 4\n";
    }
    else if (n == 5)
    {
        cout << "1 4 3 2 5\n";
    }
    else if (n == 6)
    {
        cout << "1 2 5 6 3 4\n";
    }
    else if (n == 7)
    {
        cout << "1 2 3 4 7 6 5\n";
    }
    else if (n == 8)
    {
        cout << "1 2 3 4 7 6 5 8\n";
    }
    else if (n == 9)
    {
        cout << "1 2 3 4 7 6 5 8 9\n";
    }
    else if (n == 10)
    {
        cout << "1 2 3 4 7 6 5 8 9 10\n";
    }
    else if (n % 5 == 0)
    {
        for (int i = n - 2; i >= 3; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 4; i <= n - 1; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n - 4; i >= 1; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 2; i <= n - 3; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n; i >= 5; i -= 5)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    else if (n % 5 == 1)
    {
        for (int i = n - 2; i >= 4; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 3; i <= n - 3; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n; i >= 1; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 2; i <= n - 4; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n - 1; i >= 5; i -= 5)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    else if (n % 5 == 2)
    {
        for (int i = n - 2; i >= 5; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 2; i <= n; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n - 3; i >= 4; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 3; i <= n - 4; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n - 1; i >= 1; i -= 5)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    else if (n % 5 == 3)
    {
        for (int i = n - 2; i >= 1; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 4; i <= n - 4; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n - 1; i >= 2; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 3; i <= n; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n - 3; i >= 5; i -= 5)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    else if (n % 5 == 4)
    {
        for (int i = n - 2; i >= 2; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 1; i <= n - 3; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n; i >= 4; i -= 5)
        {
            cout << i << " ";
        }
        for (int i = 3; i <= n - 1; i += 5)
        {
            cout << i << " ";
        }
        for (int i = n - 4; i >= 5; i -= 5)
        {
            cout << i << " ";
        }
        cout << "\n";
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