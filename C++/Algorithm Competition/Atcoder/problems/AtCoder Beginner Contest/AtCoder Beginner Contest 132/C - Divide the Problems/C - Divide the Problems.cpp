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
    int *d = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> d[i];
    }
    qsort(d, n, sizeof(int), sort);
    cout << d[(n + 1) / 2] - d[(n - 1) / 2] << endl;
    return 0;
}