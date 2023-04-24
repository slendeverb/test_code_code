#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin>>s;
    int n;
    cin>>n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        string sub = s.substr(a, b);
        s.erase(a, b);
        string match1, match2;
        size_t pos = s.find(match1) + match1.size();
        if (pos != string::npos)
        {
            s.insert(pos, sub);
        }
        else
        {
            s += sub;
        }
    }
    cout<<s<<"\n";
    return 0;
}