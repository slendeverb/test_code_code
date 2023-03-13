#include <bits/stdc++.h>
using namespace std;

int n, m, ans, trans;
int main()
{
    cin >> n >> m;
    int grid[n + 1][m + 1];
    int x[9] = {0, 0, 0, -1, -1, -1, -2, -2, -3};
    int y[9] = {-1, -2, -3, 0, -1, -2, 0, -1, 0};
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            cin >> grid[i][j];
            int trans = INT_MIN;
            for (int t = 0; t < 9; ++t)
            {
                if (i + x[t] > 0 && j + y[t] > 0)
                {
                    trans = max(trans, grid[i + x[t]][j + y[t]]);
                }
            }
            if (trans != INT_MIN)
                grid[i][j] += trans;
        }

    cout << grid[n][m] << "\n";
    return 0;
}