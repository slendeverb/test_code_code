#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    double over60 = 0, over85 = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x >= 60)
        {
            over60++;
        }
        if (x >= 85)
        {
            over85++;
        }
    }
    double rate_over60 = over60 / n;
    double rate_over85 = over85 / n;
    printf("%.0lf%%\n%.0lf%%\n", rate_over60 * 100, rate_over85 * 100);
    return 0;
}