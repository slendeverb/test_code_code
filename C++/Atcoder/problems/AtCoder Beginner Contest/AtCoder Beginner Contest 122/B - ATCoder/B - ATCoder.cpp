#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int count = 0;
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'A' || s[i] == 'C' || s[i] == 'G' || s[i] == 'T')
        {
            count++;
            ans = max(ans, count);
        }
        else
        {
            count = 0;
        }
    }
    cout << ans << endl;
    return 0;
}