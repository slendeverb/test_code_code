#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int arr[200005];
int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        memset(arr, 0, sizeof(arr));
        int n = 0;
        cin >> n;
        int count = 0;
        for (int i = 1; i <= n; i++)
        {
            int x = 0;
            cin >> x;
            while (x % 2 == 0)
            {
                count++;
                x /= 2;
            }
            x = i;
            while (x % 2 == 0)
            {
                arr[x]++;
                x /= 2;
            }
        }
        if (count >= n)
        {
            cout << 0 << "\n";
            continue;
        }
        sort(arr + 1, arr + n + 1);
        int ans = -1;
        int ret = 0;
        for (int i = n; i >= 1; i--)
        {
            if (arr[i])
            {
                count += arr[i];
                ret++;
            }
            if (count >= n)
            {
                ans = ret;
                break;
            }
        }
        cout << ans << "\n";
    }
}