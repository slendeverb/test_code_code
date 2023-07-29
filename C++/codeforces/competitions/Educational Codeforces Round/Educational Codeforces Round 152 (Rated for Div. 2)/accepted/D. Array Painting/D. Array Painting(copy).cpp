#include <iostream>
using namespace std;

const int maxn = 2e5 + 10;

int a[maxn];
bool vis[maxn];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!a[i])
        {
            continue;
        }
        int j = i, ok = 0;
        while (j <= n && a[j] >= 1)
        {
            if (a[j] == 2)
            {
                ok = 1;
            }
            j++;
        }
        j--, ans++;
        if (ok)
        {
            for (int k = i - 1; k <= j + 1; k++)
            {
                vis[k] = true;
            }
        }
        else
        {
            for (int k = i; k <= j; k++)
            {
                vis[k] = true;
            }
            if (i - 1 >= 1 && !vis[i - 1])
            {
                vis[i - 1] = true;
            }
            else if (j + 1 <= n && !vis[j + 1])
            {
                vis[j + 1] = true;
            }
        }
        i = j;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}