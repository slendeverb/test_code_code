#include <iostream>
#include <string>
#include <map>
using namespace std;

map<int, char> mp;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        mp.clear();
        int n = 0;
        cin >> n;
        int a[51] = {0};
        string s;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        cin >> s;
        int flag=1;
        for (int i = 0; i < n; i++)
        {
            if(!mp[a[i]])
            {
                mp[a[i]]=s[i];
            }
        }
        for(int i=0;i<n;i++)
        {
            if(mp[a[i]]!=s[i])
            {
                flag=0;
            }
        }
        if(flag)
        {
            cout<<"YES"<<"\n";
        }
        else
        {
            cout<<"NO"<<"\n";
        }
    }

    return 0;
}