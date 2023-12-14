#include <iostream>
#include <queue>
using namespace std;

const int maxk = 1e6 + 10;

struct node
{
    long long value;
    int location;
    bool operator<(const node &a) const
    {
        return value < a.value;
    }
};

priority_queue<long long> s[maxk];
priority_queue<node> maxx;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long minn = 1e18;
        while (!maxx.empty())
        {
            maxx.pop();
        }
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++)
        {
            while (!s[i].empty())
            {
                s[i].pop();
            }
            int c;
            cin >> c;
            for (int j = 1; j <= c; j++)
            {
                int x;
                cin >> x;
                s[i].push(x);
            }
        }
        for (int i = 1; i <= k; i++)
        {
            minn = min(minn, s[i].top());
            maxx.push({s[i].top(), i});
            s[i].pop();
        }
        long long ans = maxx.top().value - minn;
        while (true)
        {
            node tmp = maxx.top();
            maxx.pop();
            if (minn == tmp.value)
            {
                ans = 0;
                break;
            }
            if (!s[tmp.location].empty())
            {
                ans = min(ans, tmp.value - minn);
                minn = min(minn, s[tmp.location].top());
                maxx.push({s[tmp.location].top(), tmp.location});
                s[tmp.location].pop();
            }
            else
            {
                ans = min(ans, tmp.value - minn);
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}