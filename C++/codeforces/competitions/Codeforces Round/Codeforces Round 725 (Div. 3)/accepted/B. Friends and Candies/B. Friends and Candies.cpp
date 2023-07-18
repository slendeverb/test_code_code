#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0;
        cin >> n;
        int *arr = new int[n + 1];
        long long sum = 0;
        int ans = 0;
        int flag = 1;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            sum += arr[i];
            if (arr[i] != arr[0])
            {
                flag = 0;
            }
        }
        if (sum % n != 0)
        {
            ans = -1;
        }
        else if (n == 1 || flag)
        {
            ans = 0;
        }
        else
        {
            int average = sum / n;
            for (int i = 0; i < n; i++)
            {
                if (arr[i] > average)
                {
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}