#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

map<char, int> m;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        bool flag = 0;
        m.clear();
        if (s.size() == 1)
        {
            cout << "NaN\n";
            continue;
        }
        for (int i = 0; i < s.size(); i++)
        {
            if (m[s[i]] == 0)
            {
                m[s[i]]++;
            }
            else
            {
                break;
            }
            string b = s.substr(i + 1);
            string b1 = b;
            reverse(b.begin(), b.end());
            if (b1 == b)
            {
                cout << "HE\n";
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            cout << "NaN\n";
        }
    }
    return 0;
}