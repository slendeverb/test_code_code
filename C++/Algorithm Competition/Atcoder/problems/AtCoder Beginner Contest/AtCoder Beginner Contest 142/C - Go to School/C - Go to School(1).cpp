#include <iostream>
#include <vector>
using namespace std;

void sort(int *a, int *b, int sz)
{
    for (int i = 0; i < sz - 1; i++)
    {
        for (int j = 0; j < sz - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                int tmp1 = b[j];
                b[j] = b[j + 1];
                b[j + 1] = tmp1;
            }
        }
    }
}
int main()
{
    int n = 0;
    cin >> n;
    int *a = new int[n];
    int *b = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = i + 1;
    }
    sort(a, b, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", b[i]);
    }
    cout << endl;
    return 0;
}