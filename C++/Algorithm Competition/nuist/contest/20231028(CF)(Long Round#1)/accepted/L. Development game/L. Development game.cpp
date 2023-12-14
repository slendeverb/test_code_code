#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 10;
const int M = 105;

int n, m, K;

struct node
{
    int i, j, op, a, b, d, v;
    void input()
    {
        cin >> i >> j >> op >> a >> b >> d >> v;
    }
} judge[M];

int a[N];

void solve()
{
    cin >> n >> m >> K;
    for (int i = 1; i <= m; i++)
    {
        judge[i].input();
    }
    int maxGrade = 0;

    // random_device rnd;
    // mt19937_64 gen(rnd());
    // uniform_int_distribution<> distrib(0, K);

    int tmp = n;
    int maxx = 0;

    while (tmp)
    {
        maxx = maxx * 10 + K;
        tmp--;
    }

    for (int i = 0; i <= maxx; i++)
    {
        int flag = 1;
        memset(a, 0, sizeof(a));
        int tmp = i;
        int pos = 0;
        while (tmp)
        {
            if (tmp % 10 > K)
            {
                flag = 0;
                break;
            }
            a[++pos] = tmp % 10;
            tmp /= 10;
        }
        if (!flag)
        {
            continue;
        }
        int tmpGrade = 0;

        for (int j = 1; j <= m; j++)
        {
            if (judge[j].op == 0)
            {
                if (judge[j].a * a[judge[j].i] + judge[j].b * a[judge[j].j] <= judge[j].d)
                {
                    tmpGrade += judge[j].v;
                }
            }
            else if (judge[j].op == 1)
            {
                if (judge[j].a * a[judge[j].i] + judge[j].b * a[judge[j].j] >= judge[j].d)
                {
                    tmpGrade += judge[j].v;
                }
            }
        }
        maxGrade = max(maxGrade, tmpGrade);
    }

    cout << maxGrade << endl;
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