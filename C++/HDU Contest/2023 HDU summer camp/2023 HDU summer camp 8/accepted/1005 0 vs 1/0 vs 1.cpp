#include <bits/stdc++.h>
using namespace std;

int n;
string s;

void solve()
{
    cin >> n >> s;
    if (n == 1)
    {
        if (s[0] == '1')
        {
            cout << "1\n";
            return;
        }
        else
        {
            cout << "-1\n";
            return;
        }
    }
    if (s[0] == '1' && s[n - 1] == '1')
    {
        cout << "1\n";
        return;
    }
    int l = 0, r = n - 1, mid, num0l, num0r, num1l, num1r;
    int cur = 0;
    bool ok = 0;
    while (l <= r)
    {
        ok = 0;
        mid = (l + r) >> 1;
        num0l = 0, num0r = 0, num1l = 0, num1r = 0;
        if (cur == 0)
        {
            if (s[l] == '0')
            {
                ok = 1;
                for (int i = l; i <= l + 2 && i <= mid; i++)
                {
                    if (s[i] == '0')
                    {
                        num0l++;
                    }
                    else
                    {
                        num1l++;
                    }
                }
            }
            if (s[r] == '0')
            {
                ok = 1;
                for (int i = r; i >= r - 2 && i >= mid + 1; i--)
                {
                    if (s[i] == '0')
                    {
                        num0r++;
                    }
                    else
                    {
                        num1r++;
                    }
                }
            }
            if (!ok)
            {
                cout << "1\n";
                return;
            }
            if (num0l > num0r)
            {
                l++;
            }
            else if (num0l < num0r)
            {
                r--;
            }
            else
            {
                if (num1l < num1r)
                {
                    l++;
                }
                else
                {
                    r--;
                }
            }
        }
        else
        {
            if (s[l] == '1')
            {
                ok = 1;
                for (int i = l; i <= l + 2 && i <= mid; i++)
                {
                    if (s[i] == '0')
                    {
                        num0l++;
                    }
                    else
                    {
                        num1l++;
                    }
                }
            }
            if (s[r] == '1')
            {
                ok = 1;
                for (int i = r; i >= r - 2 && i >= mid + 1; i--)
                {
                    if (s[i] == '0')
                    {
                        num0r++;
                    }
                    else
                    {
                        num1r++;
                    }
                }
            }
            if (!ok)
            {
                cout << "0\n";
                return;
            }
            if (num1l > num1r)
            {
                l++;
            }
            else if (num1l < num1r)
            {
                r--;
            }
            else
            {
                if (num0l < num0r)
                {
                    l++;
                }
                else
                {
                    r--;
                }
            }
        }
        cur ^= 1;
    }
    cout << "-1\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}