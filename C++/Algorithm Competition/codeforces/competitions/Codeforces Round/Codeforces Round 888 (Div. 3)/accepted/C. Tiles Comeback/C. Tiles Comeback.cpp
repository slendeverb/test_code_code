#include <iostream>
#include <map>
using namespace std;

const int maxn = 2e5 + 10;

int c[maxn];

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        map<int, int> m;
        for (int i = 1; i <= n; i++)
        {
            cin >> c[i];
            m[c[i]]++;
        }
        if (m[c[1]] == n)
        {
            cout << "YES\n";
            continue;
        }
        int pos1 = n;
        int cnt1 = 0;
        while (pos1 > 0)
        {
            if (c[pos1] == c[n])
            {
                cnt1++;
                if (cnt1 == k)
                {
                    break;
                }
            }
            pos1--;
        }
        if (pos1 == 0)
        {
            cout << "NO\n";
        }
        else
        {
            if (c[1] == c[n])
            {
                cout << "YES\n";
                continue;
            }
            int pos2 = 1;
            int cnt2 = 0;
            while (pos2 < pos1)
            {
                if (c[pos2] == c[1])
                {
                    cnt2++;
                    if (cnt2 == k)
                    {
                        break;
                    }
                }
                pos2++;
            }
            if (pos2 < pos1)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
    return 0;
}