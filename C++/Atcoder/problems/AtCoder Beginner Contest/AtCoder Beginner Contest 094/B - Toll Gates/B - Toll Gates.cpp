#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n = 0, m = 0, x = 0;
    cin >> n >> m >> x;
    vector<int> a(n + 1, 0);
    int ans_left = 0, ans_right = 0;
    for (int i = 1; i <= m; i++)
    {
        int tmp = 0;
        cin >> tmp;
        a[tmp]++;
    }
    for (int i = x; i >= 1; i--)
    {
        ans_left += a[i];
    }
    for (int i = x; i <= n; i++)
    {
        ans_right += a[i];
    }
    int ans = min(ans_left, ans_right);
    cout << ans << endl;
    return 0;
}