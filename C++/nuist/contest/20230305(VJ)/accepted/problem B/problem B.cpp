#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string a, b;
int k;
const int N = 2010;
int dp[N][N];
// dp[i][j]代表长度为i和长度为j的字符串的“距离”

int main()
{
    cin >> a >> b;
    cin >> k;
    for (int i = 0; i <= a.size(); i++) // 设置另一个字符串为空字符串
    {
        dp[i][0] = i * k;
    }
    for (int j = 0; j <= b.size(); j++)
    {
        dp[0][j] = j * k;
    }
    for (int i = 1; i <= a.size(); i++)
    {
        for (int j = 1; j <= b.size(); j++)
        {
            dp[i][j] = min(dp[i - 1][j - 1] + abs(int(a[i - 1] - b[j - 1]) /*这里写i-1是因为string从0开始存储字符串*/), min(dp[i - 1][j] + k, dp[i][j - 1] + k));
        }
    }
    cout << dp[a.size()][b.size()] << "\n";
    return 0;
}