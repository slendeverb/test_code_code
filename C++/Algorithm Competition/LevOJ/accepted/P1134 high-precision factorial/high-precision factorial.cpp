#include <iostream>
#include <cstring>
using namespace std;

const int N = 3010;
int a[N];

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        int pos = 0;
        a[0] = 1;
        int carry = 0;
        for (int i = 1; i <= n; i++)
        {
            int s = 0;
            for (int j = 0; j <= pos; j++)
            {
                s = a[j] * i + carry;
                a[j] = s % 10;
                carry = s / 10;
            }
            while (carry)
            {
                pos++;
                a[pos] = carry % 10;
                carry /= 10;
            }
        }
        for (int i = pos; i >= 0; i--)
        {
            cout << a[i];
        }
        cout << "\n";
        memset(a, 0, sizeof(a));
    }
    return 0;
}