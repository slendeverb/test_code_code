#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;
long long p[N];
long long tmp[N];
int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    sort(p, p + n);
    tmp[1] = p[0];
    for (int i = 2; i <= n; i++)
    {
        tmp[i] = tmp[i - 1] + p[i - 1];
    }
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << tmp[n - x + y] - tmp[n - x] << "\n";
    }
    return 0;
}