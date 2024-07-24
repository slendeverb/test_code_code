#include <bits/stdc++.h>
using namespace std;

int sort(const void *str1, const void *str2)
{
    return *((int *)str1) - *((int *)str2);
}
int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int n = 0, l = 0, r = 0;
        cin >> n >> l >> r;
        int *arr = new int[n + 1];
        int min = 0;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            min = min < arr[i] ? min : arr[i];
        }
        if (min >= r)
        {
            ans = 0;
        }
        else
        {
            qsort(arr, n, sizeof(int), sort);
            for (int i = 0; i < n; i++)
            {
                if (arr[i] >= r)
                {
                    break;
                }
                for (int j = i + 1; j < n; j++)
                {
                    if (arr[i] + arr[j] < l)
                    {
                        continue;
                    }
                    else if (arr[i] + arr[j] > r)
                    {
                        break;
                    }
                    else
                    {
                        ans++;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}