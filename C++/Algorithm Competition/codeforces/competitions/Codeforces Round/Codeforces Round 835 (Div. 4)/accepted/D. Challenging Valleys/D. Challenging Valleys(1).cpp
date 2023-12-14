#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool Equal(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != a[0])
        {
            return false;
        }
    }
    return true;
}
void solve()
{
    int n;
    cin >> n;
    int flag = 0;
    int l = n - 2, r = 1;
    int *a = new int[n];
    int count = 0;
    int min = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] < min)
        {
            min = a[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i != 0 && i != n - 1 && a[i] == min && a[i - 1] > a[i] && a[i] < a[i + 1])
        {
            count++;
        }
        else if (a[i] == min)
        {
            break;
        }
    }
    if (count == 1)
    {
        flag = 1;
    }
    count = 0;
    while (r <= n - 1)
    {
        if (a[r] == a[r - 1])
        {
            count++;
        }
        else if (a[r] > a[r - 1] && count)
        {
            flag = 1;
            break;
        }
        else if (a[r] < a[r - 1])
        {
            break;
        }
        r++;
    }
    count = 0;
    while (l >= 0)
    {
        if (a[l] == a[l + 1])
        {
            count++;
        }
        else if (a[l] < a[l + 1] && count)
        {
            flag = 1;
            break;
        }
        else if (a[l] > a[l + 1])
        {
            break;
        }
        l--;
    }
    if (flag || n == 1 || Equal(a, n))
    {
        cout << "YES"
             << "\n";
    }
    else
    {
        cout << "NO"
             << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}