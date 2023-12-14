#include <iostream>
#include <climits>
using namespace std;

long long tmp[9];

int main()
{
    int n;
    cin >> n;
    long long ans = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        tmp[1] = max(tmp[1] + a + b + c, tmp[1]);
        ans = max(ans, tmp[1]);

        tmp[2] = max(tmp[2] - a + b + c, tmp[2]);
        ans = max(ans, tmp[2]);

        tmp[3] = max(tmp[3] + a - b + c, tmp[3]);
        ans = max(ans, tmp[3]);

        tmp[4] = max(tmp[4] + a + b - c, tmp[4]);
        ans = max(ans, tmp[4]);

        tmp[5] = max(tmp[5] - a - b + c, tmp[5]);
        ans = max(ans, tmp[5]);

        tmp[6] = max(tmp[6] - a + b - c, tmp[6]);
        ans = max(ans, tmp[6]);

        tmp[7] = max(tmp[7] + a - b - c, tmp[7]);
        ans = max(ans, tmp[7]);

        tmp[8] = max(tmp[8] - a - b - c, tmp[8]);
        ans = max(ans, tmp[8]);
    }
    cout << ans << "\n";

    return 0;
}