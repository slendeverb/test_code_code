#include <iostream>
using namespace std;

int min_distance(int x, int k)
{
    return (x < (k - x)) ? 2 * x : 2 * (k - x);
}
int main()
{
    int n = 0;
    int k = 0;
    cin >> n >> k;
    int x = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        sum += min_distance(x, k);
    }
    cout << sum << endl;
    return 0;
}