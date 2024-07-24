#include <bits/stdc++.h>
using namespace std;

// 首先题目一定有解，是这样的，对于任何一个地雷图，我们把他反转，那么点数仍然是一样的，
// 所以，如果正图达不到，那么反转的图一定可以，正图的一样的点数必定是小于 $\frac{n * m}{2}$，或大于 $\frac{n * m}{2}$
// 小于的话，那么一定可以点数一样，大于的话，那么反图一定可以点数一样

const int N = 1005;
vector<string> A, B;

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        A.emplace_back(s);
    }
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        B.emplace_back(s);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (A[i][j] != B[i][j])
            {
                cnt++;
            }
        }
    }
    if (cnt <= n * m / 2)
    {
        for (int i = 0; i < n; i++)
        {
            cout << A[i] << "\n";
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (A[i][j] == '.')
                {
                    A[i][j] = 'X';
                }
                else
                {
                    A[i][j] = '.';
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            cout << A[i] << "\n";
        }
    }
}

int main()
{
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}