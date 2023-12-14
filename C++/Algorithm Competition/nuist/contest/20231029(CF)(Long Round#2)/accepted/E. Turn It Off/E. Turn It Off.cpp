#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

const int N = 2e5 + 5;
int n, k;
string s;

bool check(int mid)
{
    size_t pos = 0;
    int cnt = 0;
    while (pos < n)
    {
        pos = s.find_first_of("1", pos);
        if (pos == string::npos)
        {
            break;
        }
        pos += mid;
        cnt++;
    }
    return cnt <= k;
}

void solve()
{
    cin >> n >> k;
    cin >> s;
    int l = 1, r = ceil((double)n / k) + 1;
    while (l < r)
    {
        int mid = ((r - l) >> 1) + l;
        if (check(mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << r << endl;
}

signed main()
{
    // ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    FILE *in = freopen("./test/in.txt", "r", stdin), *out = freopen("./test/out.txt", "w", stdout);
    int T = 1;
    cin >> T;
    // init();
    while (T--)
    {
        solve();
    }
    return 0;
}