#include <iostream>
#include <string>
using namespace std;

int t, n;
string s;

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n >> s;
        int ans0 = 0, ans1 = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (s[i] == '0' && s[i + 1] == '0')
            {
                ans0++;
            }
            if (s[i] == '1' && s[i + 1] == '1')
            {
                ans1++;
            }
        }
        cout << max(ans0, ans1) << "\n";
    }
    return 0;
}