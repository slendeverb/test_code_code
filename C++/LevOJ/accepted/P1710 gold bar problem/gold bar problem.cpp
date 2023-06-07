#include <iostream>
#include <climits>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        int minn = INT_MAX;
        int maxx = INT_MIN;
        int x;
        for (int i = 1; i <= n; i++)
        {
            cin >> x;
            minn = min(minn, x);
            maxx = max(maxx, x);
        }
        cout << maxx << " " << minn << "\n";
    }
    return 0;
}