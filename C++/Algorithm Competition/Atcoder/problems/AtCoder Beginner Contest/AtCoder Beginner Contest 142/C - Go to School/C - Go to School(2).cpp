#include <iostream>
#include <map>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        cin >> x;
        mp[x] = i + 1;
    }
    for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        cout << it->second << " ";
    }
    cout << endl;
    return 0;
}