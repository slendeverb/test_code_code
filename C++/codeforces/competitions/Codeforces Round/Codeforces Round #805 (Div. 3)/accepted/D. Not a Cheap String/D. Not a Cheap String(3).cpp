#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

const int N = 2 * 10e5;
map<char, int> mp;
int a[N];
int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        mp.clear();
        string str;
        int p = 0;
        cin >> str;
        cin >> p;
        int i = 0;
        int sum = 0;
        for (i = 0; i < str.size(); i++)
        {
            a[i] = str[i] - 'a';
        }
        sort(a, a + str.size());
        for (i = 0; i < str.size(); i++)
        {
            if (sum + a[i] + 1 <= p)
            {
                sum += a[i] + 1;
                mp[a[i] + 'a']++;
            }
        }
        for (i = 0; i < str.size(); i++)
        {
            if (mp[str[i]] != 0)
            {
                cout << str[i];
                mp[str[i]]--;
            }
        }
        cout << endl;
    }
    return 0;
}