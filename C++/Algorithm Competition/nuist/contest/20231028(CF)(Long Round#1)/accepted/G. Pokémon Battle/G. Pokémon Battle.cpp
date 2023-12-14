#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 1e5 + 5;
int n, m, K;

struct Pokemon
{
    int h, a, b, c, d, e, w, energe;
    void input()
    {
        cin >> h >> a >> b >> c >> d >> e >> w;
    }
} Alice[N], Bob[N];

void solve()
{
    cin >> n >> m >> K;
    deque<Pokemon> qa, qb;
    for (int i = 1; i <= n; i++)
    {
        Alice[i].input();
        qa.emplace_back(Alice[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        Bob[i].input();
        qb.emplace_back(Bob[i]);
    }
    int turn = 0;
    while (qa.size() && qb.size())
    {
        Pokemon a = qa.front();
        qa.pop_front();
        Pokemon b = qb.front();
        qb.pop_front();

        int maxDamageAlice = max(0LL, max(a.a - b.c, a.b - b.d));

        if (a.energe >= a.e)
        {
            if (a.w > maxDamageAlice)
            {
                maxDamageAlice = a.w;
                a.energe -= a.e;
            }
            else
            {
                a.energe++;
            }
        }
        else
        {
            a.energe++;
        }

        b.h -= maxDamageAlice;
        qa.emplace_back(a);
        a = qa.front();
        qa.pop_front();

        if (b.h <= 0)
        {
            if (qb.size())
            {
                b = qb.front();
                qb.pop_front();
            }
            else
            {
                cout << "Alice\n";
                return;
            }
        }

        int maxDamageBob = max(0LL, max(b.a - a.c, b.b - a.d));
        if (b.energe >= b.e)
        {
            if (b.w > maxDamageBob)
            {
                maxDamageBob = b.w;
                b.energe -= b.e;
            }
            else
            {
                b.energe++;
            }
        }
        else
        {
            b.energe++;
        }

        a.h -= maxDamageBob;
        qb.emplace_back(b);

        if (a.h > 0)
        {
            qa.emplace_front(a);
        }

        turn++;
        if (turn >= K)
        {
            if (qa.size() && qb.size())
            {
                cout << "Draw\n";
                return;
            }
            else
            {
                if (!qa.size())
                {
                    cout << "Bob\n";
                    return;
                }
                else if (!qb.size())
                {
                    cout << "Alice\n";
                    return;
                }
            }
        }
    }

    if (!qa.size())
    {
        cout << "Bob\n";
        return;
    }
    else if (!qb.size())
    {
        cout << "Alice\n";
        return;
    }
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    freopen("C:/Users/slendeverb/Documents/code_code/test/in.txt", "r", stdin);
    freopen("C:/Users/slendeverb/Documents/code_code/test/out.txt", "w", stdout);
    int T = 1;
    // cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}