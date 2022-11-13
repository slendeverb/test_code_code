#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0;
        char c = 0;
        string s;
        cin >> n >> c >> s;
        if (c == 'g')
        {
            cout << 0 << "\n";
            continue;
        }
        s = s + s;
        int pos = -1, ans = -1;
        for (int i = 0; i < 2 * n; i++)
        {
            if (s[i] == c && pos == -1)
            {
                pos = i;
            }
            if (s[i] == 'g' && pos != -1)
            {
                ans = max(ans, i - pos);
                pos = -1;
                if (i > n)
                {
                    break;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}