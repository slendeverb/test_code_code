#include <iostream>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

const int maxn = 50010 << 1;
int t, n, n2, m, DX, DY;

set<pair<int, int>> ans, done;

struct cor
{
    int x, y;
    cor operator-(const cor &b) const
    {
        return cor(x - b.x, y - b.y);
    }
    cor(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

} a[maxn], b[maxn], q[maxn], pool[maxn];

bool cmp1(const cor &a, const cor &b)
{
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmp2(const cor &a, const cor &b)
{
    return a.x == b.x ? a.y > b.y : a.x < b.x;
}

bool cmp3(const cor &a, const cor &b)
{
    if (a.x == b.x)
    {
        return DY >= 0 ? a.y < b.y : a.y > b.y;
    }
    return DX >= 0 ? a.x < b.x : a.x > b.x;
}

void check(int dx, int dy)
{
    if (done.find(pair<int, int>(dx, dy)) != done.end())
    {
        return;
    }
    done.insert(pair<int, int>(dx, dy));
    done.insert(pair<int, int>(-dx, -dy));
    map<pair<int, int>, int> m;
    int cnt = 0;
    for (int i = 1; i <= n2; i++)
    {
        m[pair<int, int>(b[i].x, b[i].y)]++;
    }
    DX = dx, DY = dy;
    sort(b + 1, b + 1 + n2, cmp3);
    for (int i = 1; i <= n2; i++)
    {
        int &pos = m[pair<int, int>(b[i].x, b[i].y)];
        if (!pos)
        {
            continue;
        }
        pos--;
        cnt++;
        int &nxt = m[pair<int, int>(b[i].x + dx, b[i].y + dy)];
        if (!nxt)
        {
            return;
        }
        nxt--;
    }
    if (cnt == n)
    {
        ans.insert(pair<int, int>(dx, dy));
        ans.insert(pair<int, int>(-dx, -dy));
    }
}

long long cross(const cor &a, const cor &b)
{
    return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

void findline(const cor &A, const cor &B)
{
    int cp = 0;
    for (int i = 1; i <= n2; i++)
    {
        if (!cross(B, a[i] - A))
        {
            pool[++cp] = a[i];
        }
    }
    for (int i = 1; i <= cp; i++)
    {
        for (int j = 1; j <= cp; j++)
        {
            check(pool[i].x - pool[j].x, pool[i].y - pool[j].y);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n;
        n2 = n << 1;
        for (int i = 1; i <= n2; i++)
        {
            cin >> a[i].x >> a[i].y;
            b[i] = a[i];
        }
        ans.clear();
        done.clear();
        check(0, 0);
        sort(a + 1, a + 1 + n2, cmp1);
        findline(a[1], cor(0, 1));
        findline(a[n2], cor(0, 1));
        m = 0;
        for (int i = 1; i <= n2; i++)
        {
            if (i > 1 && a[i].x == a[i - 1].x)
            {
                continue;
            }
            while (m > 1 && 1ll * (q[m].y - q[m - 1].y) * (a[i].x - q[m].x) >= 1ll * (a[i].y - q[m].y) * (q[m].x - q[m - 1].x))
            {
                m--;
            }
            q[++m] = a[i];
        }
        for (int i = 1; i < m; i++)
        {
            findline(q[i], q[i + 1] - q[i]);
        }
        sort(a + 1, a + 1 + n2, cmp2);
        m = 0;
        for (int i = 1; i <= n2; i++)
        {
            if (i > 1 && a[i].x == a[i - 1].x)
            {
                continue;
            }
            while (m > 1 && 1ll * (q[m].y - q[m - 1].y) * (a[i].x - q[m].x) <= 1ll * (a[i].y - q[m].y) * (q[m].x - q[m - 1].x))
            {
                m--;
            }
            q[++m] = a[i];
        }
        for (int i = 1; i < m; i++)
        {
            findline(q[i], q[i + 1] - q[i]);
        }
        cout << ans.size() << "\n";
        for (auto ele : ans)
        {
            cout << ele.first << " " << ele.second << "\n";
        }
    }
    return 0;
}