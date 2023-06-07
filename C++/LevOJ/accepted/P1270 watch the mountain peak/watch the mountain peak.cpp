#include <iostream>
#include <queue>
using namespace std;

const int maxn = 1e5 + 10;

int main()
{
    int n;
    while (cin >> n)
    {
        queue<long long> q;
        for (int i = 1; i <= n; i++)
        {
            long long x;
            cin >> x;
            if (q.empty())
            {
                q.push(x);
            }
            else
            {
                if (x > q.back())
                {
                    q.push(x);
                }
            }
        }
        cout << q.size() << "\n";
    }
    return 0;
}