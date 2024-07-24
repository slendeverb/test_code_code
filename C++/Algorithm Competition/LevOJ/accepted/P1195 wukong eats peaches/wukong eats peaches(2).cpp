#include <iostream>
using namespace std;

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int ans = 1;
        while (--n)
        {
            ans = (ans + 1) * 2;
        }
        printf("%d\n", ans);
    }
    return 0;
}