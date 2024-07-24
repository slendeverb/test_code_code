#include <iostream>
using namespace std;

const int N = 2e6 + 10;
int n;
int t[N];

long long sum = 0;
long long ans = 0;

int main()
{
    // ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    for (int i = 2; i <= 2 * n - 2; i += 2)
    {
        cin >> t[i];
        sum += t[i];
    }
    for (int i = 1; i <= 2 * n - 1; i += 2)
    {
        cin >> t[i];
        sum += t[i];
    }
    long long sum1 = 0;
    int tmp1 = 0;
    for (int i = 1; i <= 2 * n - 1; i++)
    {
        sum1 += t[i];
        if (sum1 > sum / 2)
        {
            tmp1 = i - 1;
            break;
        }
    }
    long long sum2 = 0;
    long long tmp2 = 0;
    for (int i = 2 * n - 1; i >= 1; i--)
    {
        sum2 += t[i];
        if (sum2 > sum / 2)
        {
            tmp2 = i + 1;
            break;
        }
    }
    if (tmp1 + 1 == tmp2 - 1 && (tmp1 + 1) % 2 == 1)
    {
        ans = t[tmp1 + 1] - abs(sum1 - sum2);
    }
    cout << ans << "\n";
    return 0;
}