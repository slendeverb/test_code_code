#include <bits/stdc++.h>
using namespace std;

#define int long long
int n;
const int N = 1e5 + 5;
int p[N], q[N];

int rsp(int a[], int N) // 数组a，大小N
{
    int sum = 0;
    // c是要维护的树状数组
    int *c = (int *)malloc(sizeof(int) * (N + 1));
    memset(c, 0, sizeof(int) * (N + 1));
    for (int i = 0; i < N; i++)
    {
        int k = a[i];
        // 维护c
        while (k <= N)
        {
            c[k] += 1;
            k += k & (-k);
        }
        // 求与当前a[i]构成的逆序对，也就求c中区间[k+1,N]的和
        // 树状数组区间求和一般是求[1,k]，所以我们转化一下，遍历到a[i]时c中有（i+1）个位置被标记为1,总和为（i+1）
        // 区间[k+1,N]的和 = (i+1) - 区间[1,k]的和
        k = a[i];
        int s = 0; // 区间[1,k]的和
        while (k > 0)
        {
            s += c[k];
            k -= k & (-k);
        }
        sum += (i + 1 - s); //(i+1 - s)就是当前与a[i]构成的逆序对的个数
    }
    return sum;
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
        q[n - 1 - i] = p[i];
    }
    long long sum1 = rsp(p, n);
    int minn = (sum1 & 1) ? 2 : 0;
    long long sum2 = rsp(q, n);
    int maxx = n;
    int tmpn = n;
    int cnt = 0;
    while (tmpn)
    {
        if ((tmpn & 1) == 0 && cnt != 0 && cnt != 1)
        {
            maxx ^= (1ll << cnt);
        }
        tmpn >>= 1;
        cnt++;
    }
    int t = (sum2 & 1) ? 2 : 0;
    maxx ^= t;
    if ((maxx & 1) == 0)
    {
        maxx ^= 1;
    }
    cout << minn << " " << maxx << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--)
    {
        solve();
    }
    cout.flush();
    return 0;
}