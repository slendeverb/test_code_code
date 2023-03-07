#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    string s;
    cin >> s;
    map<char, int> mp;
    for (int i = 0; i < s.size(); i++)
    {
        mp[s[i]]++;
    }
    int ans = 0;
    char ret = '0';
    for (auto it : mp)
    {
        if (ans < it.second)
        {
            ans = it.second;
            ret = it.first;
        }
    }
    cout << ret << endl;
    cout << ans << endl;
    return 0;
}