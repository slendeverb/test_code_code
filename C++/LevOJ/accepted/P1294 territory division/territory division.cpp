#include <iostream>
using namespace std;

int n, m;

int main()
{
    while (scanf("%d %d", &n, &m) != EOF)
    {
        int count = 0;
        int minn = min(n, m);
        int maxx = max(n, m);
        while (minn >= 1)
        {
            count++;
            maxx -= minn;
            int tmp1 = maxx, tmp2 = minn;
            maxx = max(tmp1, tmp2);
            minn = min(tmp1, tmp2);
        }
        cout << count << "\n";
    }
    return 0;
}