#include <iostream>
using namespace std;

int n, cnt, a[20];
bool vis[20];

int isprime(int x)
{
    if (x == 2 || x == 3)
    {
        return 1;
    }
    if (x % 6 != 1 && x % 6 != 5)
    {
        return 0;
    }
    for (int i = 5; i <= floor(sqrt((double)x)); i += 6)
    {
        if (x % i == 0 || x % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void dfs(int x)
{
    if (x == n && isprime(a[0] + a[n - 1]))
    {
        cout << 1;
        for (int i = 1; i < n; i++)
        {
            cout << " " << a[i];
        }
        cout << "\n";
    }
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i] && isprime(a[x - 1] + i))
        {
            a[x] = i;
            vis[i] = true;
            dfs(x + 1);
            vis[i] = false;
        }
    }
}

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        memset(vis, 0, sizeof(vis));
        a[0] = 1;
        printf("Case %d:\n", ++cnt);
        dfs(1);
        cout << "\n";
    }
    return 0;
}