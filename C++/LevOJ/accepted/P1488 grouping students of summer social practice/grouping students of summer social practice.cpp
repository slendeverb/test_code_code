#include <iostream>
using namespace std;

int gcd(int x, int y)
{
    int t = 0;
    while (t = x % y)
    {
        x = y;
        y = t;
    }
    return y;
}
int main()
{
    int n, m, k;
    while (scanf("%d %d %d", &n, &m, &k) != EOF)
    {
        int ret = gcd(gcd(n, m), k);
        cout << ret << endl;
    }
    return 0;
}