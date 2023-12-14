#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
int a[N];
int ret[N];
int main()
{
    int n;
    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    if (n % 2 == 0)
    {
        ans = n / 2 - 1;
    }
    else
    {
        ans = n / 2;
    }
    int tmp = 0;
    for (int i = 1; i < n; i += 2)
    {
        ret[i] = a[tmp];
        tmp++;
    }
    for (int i = 0; i < n; i += 2)
    {
        ret[i] = a[tmp];
        tmp++;
    }
    cout << ans << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << ret[i] << " ";
    }
    cout << "\n";
    return 0;
}