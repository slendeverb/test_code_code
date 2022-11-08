#include <iostream>
using namespace std;

int sort(const void *str1, const void *str2)
{
    return *((int *)str1) - *((int *)str2);
}
int main()
{
    int n = 0;
    cin >> n;
    int *v = new int[n];
    double ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    qsort(v, n, sizeof(int), sort);
    ans = (v[0] + v[1]) / 2.0;
    for (int i = 2; i < n; i++)
    {
        ans = (ans + v[i]) / 2.0;
    }
    cout << ans << endl;
    return 0;
}