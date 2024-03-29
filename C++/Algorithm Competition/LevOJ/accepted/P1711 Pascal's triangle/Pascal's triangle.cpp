#include <iostream>
#include <vector>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    if (n == 1)
    {
        cout << 1;
        return 0;
    }
    vector<long long> a(44723 + 1);
    a[0] = 1;
    for (int i = 3; i <= 44723; i++)
    {
        for (int j = i / 2; j > 0; j--)
        {
            if (j == i / 2 && i & 1)
            {
                a[j] = a[j - 1] * 2;
            }
            else
                a[j] = a[j - 1] + a[j];
            if (a[j] == n)
            {
                cout << i * (i - 1) / 2 + j + 1;
                return 0;
            }
        }
    }
    cout << n * (n + 1) / 2 + 2;
    return 0;
}