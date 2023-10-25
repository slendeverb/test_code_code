#include <iostream>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 2e5 + 10, mod = 1e9 + 7;

int T;

void solve()
{
    int h, m, k;
    scanf("%d:%d %d", &h, &m, &k);
    int time = (h * 60 + m) % (24 * 60);

    int st[N] = {0};
    int res = 0;

    while (!st[time])
    {
        st[time] = 1;
        int h = time / 60;
        int m = time % 60;
        // cout << h << " " << m << endl;
        if (h == m % 10 * 10 + m / 10)
            res++;
        time = (time + k) % (24 * 60);
    }

    printf("%d\n", res);
}

int main()
{
    scanf("%d", &T);
    while (T--)
        solve();

    return 0;
}