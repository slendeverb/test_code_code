#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e6 + 10;
char a[N];
int Next[N];
int maxx;

void cal_next(char a[], int Size)
{
    Next[1] = 0;
    for (int i = 2, j = 0; i <= Size; i++)
    {
        while (j && a[i] != a[j + 1])
        {
            j = Next[j];
        }
        if (a[i] == a[j + 1])
        {
            j++;
        }
        Next[i] = j;
        if (i != Size)
        {
            maxx = max(maxx, Next[i]);
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> k;
    cin >> (a + 1);
    cal_next(a, n);
    int x = Next[n];
    if (x == 0)
    {
        cout << -1 << "\n";
    }
    else
    {
        int count = 0;
        for (int i = 1; i <= n; i++)
        {
            if (Next[i] == Next[n])
            {
                count++;
            }
        }
        if (count == k - 1)
        {
            for (int i = 1; i <= Next[n]; i++)
            {
                cout << a[i];
            }
            cout << "\n";
        }
        else
        {
            while (x > maxx)
            {
                x = Next[x];
            }
            if (x == 0)
            {
                cout << -1 << "\n";
            }
            else
            {
                for (int j = 1; j <= Next[x]; j++)
                {
                    cout << a[j];
                }
                cout << "\n";
            }
        }
    }
    return 0;
}