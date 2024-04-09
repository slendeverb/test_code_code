#include <bits/stdc++.h>
using namespace std;

const int N{25};

int n, k1, k2, num, flag, a[N], b[N], vis[N][N], s[N * N];
const int v[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void dfs(int x, int y, int k) {
    if (x < 1 || y < 1 || x > n || y > n) {
        return;
    }
    if (b[x] < 0 || a[y] < 0 || flag == 1) {
        return;
    }
    s[k] = (x - 1) * n + (y - 1);
    if (x == n && y == n && k1 == 1 && k2 == 1) {
        flag = 1;
        num = k;
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int dx = x + v[i][0];
        int dy = y + v[i][1];
        if (vis[dx][dy] == 1) {
            continue;
        }
        --b[dx];
        --a[dy];
        --k1;
        --k2;
        vis[dx][dy] = 1;
        dfs(dx, dy, k + 1);
        ++b[dx];
        ++a[dy];
        ++k1;
        ++k2;
        vis[dx][dy] = 0;
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        k1 += a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        k2 += b[i];
    }
    flag = 0;
    vis[1][1] = 1;
    dfs(1, 1, 1);
    for (int i = 1; i <= num; ++i) {
        cout << s[i] << " ";
    }
    cout << endl;
}

int main() {
    solve();
    return 0;
}

// #include <iostream>
// #include <vector>
// using namespace std;

// struct Node {
//     int value;
//     int gridNumber;
//     bool visited;
// };

// bool check(const vector<vector<Node>>& grid,
//            const vector<vector<int>>& arrows) {
//     for (int i = 1; i <= arrows[0].size(); ++i) {
//         if (grid[0][i].value != arrows[0][i - 1] ||
//             grid[i][0].value != arrows[1][i - 1]) {
//             return false;
//         }
//     }
//     return true;
// }

// bool valid(int n, int dx, int dy) {
//     return (dx >= 1 && dx <= n) && (dy >= 1 && dy <= n);
// }

// void dfs(vector<vector<Node>>& grid,
//          const vector<vector<int>>& arrows,
//          int x,
//          int y,
//          vector<int>& ans) {
//     size_t n{arrows[0].size()};
//     if (check(grid, arrows)) {
//         if (ans.back() == n * n - 1) {
//             return;
//         }
//     }
//     int dx = x + 1, dy = y;
//     if (valid(n, dx, dy) && !grid[dx][dy].visited) {
//         grid[dx][dy].visited = true;
//         ++grid[0][dy].value;
//         ++grid[dx][0].value;
//         ans.push_back(grid[dx][dy].gridNumber);
//         dfs(grid, arrows, dx, dy, ans);
//         if (check(grid, arrows)) {
//             if (ans.back() == n * n - 1) {
//                 return;
//             }
//         }
//         ans.pop_back();
//         --grid[0][dy].value;
//         --grid[dx][0].value;
//         grid[dx][dy].visited = false;
//     }
//     dx = x - 1, dy = y;
//     if (valid(n, dx, dy) && !grid[dx][dy].visited) {
//         grid[dx][dy].visited = true;
//         ++grid[0][dy].value;
//         ++grid[dx][0].value;
//         ans.push_back(grid[dx][dy].gridNumber);
//         dfs(grid, arrows, dx, dy, ans);
//         if (check(grid, arrows)) {
//             if (ans.back() == n * n - 1) {
//                 return;
//             }
//         }
//         ans.pop_back();
//         --grid[0][dy].value;
//         --grid[dx][0].value;
//         grid[dx][dy].visited = false;
//     }
//     dx = x, dy = y + 1;
//     if (valid(n, dx, dy) && !grid[dx][dy].visited) {
//         grid[dx][dy].visited = true;
//         ++grid[0][dy].value;
//         ++grid[dx][0].value;
//         ans.push_back(grid[dx][dy].gridNumber);
//         dfs(grid, arrows, dx, dy, ans);
//         if (check(grid, arrows)) {
//             if (ans.back() == n * n - 1) {
//                 return;
//             }
//         }
//         ans.pop_back();
//         --grid[0][dy].value;
//         --grid[dx][0].value;
//         grid[dx][dy].visited = false;
//     }
//     dx = x, dy = y - 1;
//     if (valid(n, dx, dy) && !grid[dx][dy].visited) {
//         grid[dx][dy].visited = true;
//         ++grid[0][dy].value;
//         ++grid[dx][0].value;
//         ans.push_back(grid[dx][dy].gridNumber);
//         dfs(grid, arrows, dx, dy, ans);
//         if (check(grid, arrows)) {
//             if (ans.back() == n * n - 1) {
//                 return;
//             }
//         }
//         ans.pop_back();
//         --grid[0][dy].value;
//         --grid[dx][0].value;
//         grid[dx][dy].visited = false;
//     }
// }

// void solve() {
//     int n;
//     cin >> n;
//     vector<vector<Node>> grid(n + 1, vector<Node>(n + 1, Node{0, 0, 0}));
//     vector<vector<int>> arrows(2, vector<int>(n, 0));
//     int x;
//     int num = 0;
//     for (int i = 1; i <= n; ++i) {
//         for (int j = 1; j <= n; ++j) {
//             grid[i][j].gridNumber = num++;
//         }
//     }
//     for (int i = 1; i <= n; ++i) {
//         cin >> x;
//         arrows[0][i - 1] = x;
//     }
//     for (int i = 1; i <= n; ++i) {
//         cin >> x;
//         arrows[1][i - 1] = x;
//     }
//     vector<int> ans;
//     grid[1][1].visited = true;
//     ++grid[0][1].value;
//     ++grid[1][0].value;
//     ans.push_back(grid[0][0].gridNumber);
//     dfs(grid, arrows, 1, 1, ans);
//     for (const auto& x : ans) {
//         cout << x << " ";
//     }
//     cout << endl;
// }

// int main() {
//     solve();
//     return 0;
// }