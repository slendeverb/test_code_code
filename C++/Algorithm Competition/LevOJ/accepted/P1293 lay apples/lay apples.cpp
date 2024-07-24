#include <iostream>
using namespace std;

int m, n;
long long ans;

long long solve(int m, int n)
{
    if (n <= 0 || m < 0)
    {
        return 0;
    }
    if (n == 1 || m <= 1)
    {
        return 1;
    }
    return solve(m - n, n) + solve(m, n - 1);
}

int main()
{
    while (scanf("%d %d", &m, &n) != EOF)
    {
        ans = solve(m, n);
        cout << ans << "\n";
    }
    return 0;
}