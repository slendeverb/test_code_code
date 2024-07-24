#include <iostream>
using namespace std;
#include <map>

int main()
{
    int t = 0;
    cin >> t;
    map<int, int> mp1;
    map<int, int> mp2;
    while (t--)
    {
        int n = 0;
        cin >> n;
        int i = 0;
        int *p1 = new int[n + 1];
        int *p2 = new int[n + 1];
        for (i = 0; i < n; i++)
        {
            cin >> p1[i];
            cin >> p2[i];
        }
        for (i = 0; i < n; i++)
        {
            mp1[p1[i]]++;
            mp2[p2[i]]++;
        }
        int flag = 1;
        for (i = 0; i < n; i++)
        {
            if (mp1[i] > n / 2 || mp2[i] > n / 2)
            {
                cout << "NO" << endl;
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            cout << "YES" << endl;
        }
    }
    return 0;
}