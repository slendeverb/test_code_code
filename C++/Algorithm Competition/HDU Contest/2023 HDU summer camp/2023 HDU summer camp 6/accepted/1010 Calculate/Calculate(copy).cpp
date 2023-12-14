#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;
int n, q;
long long k[MAXN][31], b[MAXN][31];
int p[MAXN][31];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
        {
            cin >> k[i][0];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> b[i][0];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> p[i][0];
        }
        for (int i = 1; i <= 30; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                p[j][i] = p[p[j][i - 1]][i - 1];
                k[j][i] = k[j][i - 1] * k[p[j][i - 1]][i - 1] % MOD;
                b[j][i] = (b[j][i - 1] * k[p[j][i - 1]][i - 1] + b[p[j][i - 1]][i - 1]) % MOD;
            }
        }
        int x, l, y;
        while (q--)
        {
            cin >> x >> l >> y;
            x = p[x][0];
            for (int i = 30; i >= 0; i--)
            {
                if ((1ll << i) & l)
                {
                    y = (y * k[x][i] + b[x][i]) % MOD;
                    x = p[x][i];
                }
            }
            cout << y << "\n";
        }
    }
    cout.flush();
    return 0;
}