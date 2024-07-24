#include <iostream>
#include <cstring>
using namespace std;

const int N = 110;
char ch_a[N], ch_b[N];
int a[N], b[N], mul[2 * N];

int main()
{
    cin >> ch_a >> ch_b;
    int len_a = strlen(ch_a);
    int len_b = strlen(ch_b);
    for (int i = 0; i <= len_a - 1; i++)
    {
        a[len_a - i] = ch_a[i] - '0';
    }
    for (int i = 0; i <= len_b - 1; i++)
    {
        b[len_b - i] = ch_b[i] - '0';
    }
    for (int i = 1; i <= len_a; i++)
    {
        int carry = 0;
        for (int j = 1; j <= len_b; j++)
        {
            mul[i + j - 1] += a[i] * b[j] + carry;
            carry = mul[i + j - 1] / 10;
            mul[i + j - 1] %= 10;
        }
        mul[i + len_b] = carry;
    }
    int len_mul = len_a + len_b;
    while (mul[len_mul] == 0 && len_mul > 1)
    {
        len_mul--;
    }
    for (int i = len_mul; i >= 1; i--)
    {
        cout << mul[i];
    }
    cout << "\n";
    return 0;
}