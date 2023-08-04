#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 1e6 + 5;
int sz[MAXN];
char s[MAXN];
int Next[MAXN];

void cal_next(char a[], int Size)
{
    Next[1] = 0;
    for (int i = 2, j = 0; i <= Size; i++)
    {
        while (j && a[i] != a[j + 1])
            j = Next[j];
        if (a[i] == a[j + 1])
            j++;
        Next[i] = j;
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n, k;
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    cal_next(s, strlen(s + 1));
    for (int i = n; i >= 1; i--)
    {
        sz[i]++;
        sz[Next[i]] += sz[i];
    }
    int m = n;
    while (sz[m] < k)
    {
        m = Next[m];
    }
    if (m == 0)
    {
        cout << "-1\n";
    }
    else
    {
        for (int i = 1; i <= m; i++)
        {
            cout << s[i];
        }
        cout << "\n";
    }
    cout.flush();
    return 0;
}