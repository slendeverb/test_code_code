#include <iostream>
using namespace std;
#include <map>

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0;
        cin >> n;
        int m = n;
        map<int, int> mp1;
        int max = 0;
        int flag = 1;
        for (int i = 1; i <= n; i++)
        {
            int tmp = 0;
            cin >> tmp;
            max = max > tmp ? max : tmp;
            mp1[tmp]++;
        }

        for (int j = 0; j < 25; j++)
        {
            for (int i = 1; i <= max; i++)
            {
                if (mp1[i] > 1)
                {
                    mp1[i]--;
                    flag = 0;
                    n--;
                }
            }
        }
        if (m % 2 == 0)
        {
            cout << n << endl;
        }
        else if (flag)
        {
            cout << m << endl;
        }
        else
        {
            cout << n - 1 << endl;
        }
    }
    return 0;
}