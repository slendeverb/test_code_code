#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e6 + 5;

struct node
{
    long long value;
    long long index;

    bool operator<(const node &a)
    {
        if (value != a.value)
        {
            return value < a.value;
        }
        else
        {
            return index > a.index;
        }
    }
} a[maxn];

long long b[maxn];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].value;
        a[i].index = i;
        b[i] = a[i].value;
    }
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + n);
    long long l = 1, r = n, mid_value, mid_index;
    while (l != r)
    {
        mid_value = ((b[l] + b[r]) >> 1) + 1;
        mid_index = lower_bound(b + l, b + 1 + r, mid_value) - b;
        if (mid_index - l < r - mid_index + 1)
        {
            l++;
        }
        else
        {
            r--;
        }
    }
    cout << a[l].index << "\n";
    return 0;
}