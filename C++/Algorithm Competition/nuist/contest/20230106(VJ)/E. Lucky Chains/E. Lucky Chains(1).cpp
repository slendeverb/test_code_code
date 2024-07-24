#include <iostream>
#include <utility>
#include <vector>
using namespace std;

const int N = 1e6 + 10;
vector<pair<int, int>> v(N);

int gcd(int x, int y)
{
    int t;
    while (t = x % y)
    {
        x = y;
        y = t;
    }
    return y;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
        int cnt = 0;
        if (gcd(v[i].first, v[i].second) > 1)
        {
            cout << 0 << "\n";
            continue;
        }
        if (abs(v[i].second - v[i].first) == 1)
        {
            cout << -1 << "\n";
            continue;
        }
        for (int j = 0; gcd(v[i].first + j, v[i].second + j) == 1; j++)
        {
            cnt++;
        }
        cout << cnt << "\n";
    }
    return 0;
}