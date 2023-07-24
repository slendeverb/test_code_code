#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> v;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        v.push_back(s);
    }
    for (int i = 1; i < n; i++)
    {
        if (v[i - 1] == v[i])
        {
            continue;
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                if (v[i][j] == !(v[i - 1][j] - '0') + '0')
                {
                    continue;
                }
                else
                {
                    cout << "-1\n";
                    return 0;
                }
            }
        }
    }
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i][0] == '1')
        {
            ans1++;
        }
        if (v[0][i] == '1')
        {
            ans2++;
        }
    }
    int ans = 0;
    ans += min(ans1, n - ans1);
    ans += min(ans2, n - ans2);
    cout << ans << "\n";
    return 0;
}