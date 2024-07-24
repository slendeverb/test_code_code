#include <iostream>
using namespace std;

void reverse(int *left, int *right)
{

    while (left < right)
    {
        int tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}

int main()
{
    int n = 0;
    cin >> n;
    int *p = new int[n];
    int k = 0;
    cin >> k;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    reverse(p, p + k - 1);
    reverse(p + k, p + n - 1);
    reverse(p, p + n - 1);
    for (i = 0; i < n; i++)
    {
        cout << p[i] << endl;
    }
    return 0;
}