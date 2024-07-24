#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node
{
    int grade;
    int index;

    bool operator<(const node &a) const
    {
        return grade > a.grade;
    }
};

void solve()
{
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<node>> grades(n + 1, std::vector<node>(m + 1, node{0, 0}));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            std::cin >> grades[i][j].grade;
            grades[i][j].index = i;
        }
    }
    std::vector<std::vector<node>> gradesRotate(m + 1, std::vector<node>(n + 1, node{0, 0}));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            gradesRotate[i][j] = grades[j][i];
        }
    }
    for (int i = 1; i <= m; i++)
    {
        std::sort(gradesRotate[i].begin() + 1, gradesRotate[i].end());
    }
    std::vector<int> ans(n + 1, 0);
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            ans[gradesRotate[i][j].index] += std::max(k + 1 - j, 0);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    solve();
    return 0;
}