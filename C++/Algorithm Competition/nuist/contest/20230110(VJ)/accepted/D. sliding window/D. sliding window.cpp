#include <iostream>
#include <deque>
#include <utility>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
int n, k;
ll a[N], ans_min[N], ans_max[N];
deque<pair<ll, int>> q1;
deque<pair<ll, int>> q2;

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        while (!q1.empty() && q1.back().first > a[i])
        {
            q1.pop_back();
        }
        while (!q2.empty() && q2.back().first < a[i])
        {
            q2.pop_back();
        }
        q1.push_back({a[i], i});
        q2.push_back({a[i], i});
        if (i >= k)
        {
            while (i - k + 1 > q1.front().second)
            {
                q1.pop_front();
            }
            while (i - k + 1 > q2.front().second)
            {
                q2.pop_front();
            }
            ans_min[i] = q1.front().first;
            ans_max[i] = q2.front().first;
        }
    }
    for (int i = k; i <= n; i++)
    {
        cout << ans_min[i] << " ";
    }
    cout << "\n";
    for (int i = k; i <= n; i++)
    {
        cout << ans_max[i] << " ";
    }
    cout << "\n";
    return 0;
}