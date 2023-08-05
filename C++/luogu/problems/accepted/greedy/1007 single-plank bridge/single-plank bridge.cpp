#include <iostream>
using namespace std;

int main()
{
    int l, n;
    cin >> l >> n;
    int max_time = 0, min_time = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        max_time = max(max(l + 1 - x, x - 0), max_time);
        min_time = max(min(l + 1 - x, x - 0), min_time);
    }
    cout << min_time << " " << max_time << "\n";
    return 0;
}