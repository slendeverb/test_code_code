#include <iostream>
#include <climits>
using namespace std;

int sort(const void *str1, const void *str2)
{
    return *((int *)str1) - *((int *)str2);
}
int main()
{
    int n = 0, x = 0;
    cin >> n >> x;
    int *a = new int[n];
    long long int sum = 0;
    long long int min_x = LLONG_MAX;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
        min_x = min_x < a[i] ? min_x : a[i];
    }
    if (sum == x)
    {
        cout << n << endl;
    }
    else if (sum < x)
    {
        cout << n - 1 << endl;
    }
    else if (x < min_x)
    {
        cout << 0 << endl;
    }
    else if (x == min_x)
    {
        cout << 1 << endl;
    }
    else
    {
        qsort(a, n, sizeof(int), sort);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (x - a[i] >= 0)
            {
                x -= a[i];
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}