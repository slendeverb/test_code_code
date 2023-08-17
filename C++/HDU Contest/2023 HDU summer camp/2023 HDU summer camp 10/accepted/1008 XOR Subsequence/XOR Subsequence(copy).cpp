#include <bits/stdc++.h>
using namespace std;

#define IOS                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
using LL = long long;
using ld = long double;
using ull = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<long long, long long>;
using unl = __int128;
#define INF 1000000000
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
using UID = uniform_int_distribution<int>;

const int N = 1 << 20;
int n, m, cnt;
int a[N], b[N], c[N];
priority_queue<int, vector<int>, greater<int>> p, q;

int TOP()
{
    while (true)
    {
        if (p.empty())
        {
            return -1;
        }
        int u = p.top();
        if (!q.empty() && q.top() == p.top())
        {
            p.pop();
            q.pop();
        }
        else
        {
            return u;
        }
    }
}

void add(int x)
{
    int tmp = cnt;
    c[++cnt] = x;
    for (int i = 1; i <= tmp; i++)
    {
        c[++cnt] = x ^ c[i];
    }
    for (int i = tmp + 1; i <= cnt; i++)
    {
        q.push(c[i]);
    }
}

void solve()
{
    cin >> n;
    m = (1 << n) - 1;
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }

    cnt = 0;
    while (!p.empty())
    {
        p.pop();
    }
    while (!q.empty())
    {
        q.pop();
    }

    for (int i = 1; i <= m; i++)
    {
        p.push(b[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        int u = TOP();
        a[i] = u;
        add(u);
    }

    if (TOP() != -1)
    {
        cout << "-1\n";
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            cout << a[i] << " ";
        }
        cout << "\n";
    }
}

signed main()
{
    // IOS;
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}