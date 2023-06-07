#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        priority_queue<long long, vector<long long>, greater<long long>> q;
        long long x;
        for (int i = 1; i <= n; i++)
        {
            cin >> x;
            q.push(x);
        }
        while (q.size() > 1)
        {
            long long u = q.top();
            q.pop();
            long long v = q.top();
            q.pop();
            q.push(u * v + 1);
        }
        cout << q.top() << "\n";
    }
    return 0;
}