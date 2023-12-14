#include <iostream>
using namespace std;
#include <cmath>
typedef long long ll;

ll factorial(int n)
{
    ll p = 1;
    for (int i = 1; i <= n; i++)
    {
        p *= i;
    }
    return p;
}
int bubble_sort_count(int *x, int n)
{
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int flag = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (x[j] > x[j + 1])
            {
                int tmp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = tmp;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            return count;
        }
        else
        {
            count++;
        }
    }
    return count;
}
int main()
{
    int n = 0;
    cin >> n;
    int p[8], q[8];
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> q[i];
    }
    int p1 = bubble_sort_count(p, 8);
    int q1 = bubble_sort_count(q, 8);
    cout << fabs((factorial(n) - factorial(p1)) - (factorial(n) - factorial(q1))) << "\n";
    return 0;
}