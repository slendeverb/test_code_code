#include <iostream>
using namespace std;
#include <cmath>
#include <climits>

int main()
{
    int k = 0;
    int n = 0;
    cin >> k >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int ans = 0;
    ans = min(arr[n - 1] - arr[0], k - arr[n - 1] + arr[n - 2] - arr[0]);
    cout << ans << endl;
    return 0;
}