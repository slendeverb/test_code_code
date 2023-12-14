#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        int len = 0, k = 0, sum = 0;
        int flag = 1;
        for (int i = 0; i < s.size() - 1; i++)
        {
            if (s[i + 1] == s[i])
            {
                if (flag)
                {
                    k++;
                    len++;
                    flag = 0;
                }
                len++;
                continue;
            }
            else
            {
                flag = 1;
            }
        }
        sum = len - k;
        cout << sum << "\n";
    }
    return 0;
}