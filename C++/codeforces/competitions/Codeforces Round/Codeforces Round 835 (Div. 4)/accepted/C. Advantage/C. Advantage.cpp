#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    int max_first = INT_MIN;
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        if (s[i] > max_first)
        {
            max_first = s[i];
            x = i;
        }
    }
    int max_second = INT_MIN;
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == max_first && i != x)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        max_second = max_first;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (s[i] != max_first)
            {
                max_second = max(max_second, s[i]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] != max_first)
        {
            ans = s[i] - max_first;
        }
        else
        {
            ans = s[i] - max_second;
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}