#include <iostream>
using namespace std;
#include <vector>
#include <limits.h>

int main()
{
    int n = 0;
    cin >> n;
    int i = 0;
    int sum = INT_MAX;
    vector<int> arr(n + 1, 0);
    int min = 1000;
    int max = 0;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
        min = min < arr[i] ? min : arr[i];
        max = max > arr[i] ? max : arr[i];
    }
    for (i = min; i <= max; i++)
    {
        int tmp = 0;
        for (int j = 0; j < n; j++)
        {
            tmp += (arr[j] - i) * (arr[j] - i);
        }
        sum = sum < tmp ? sum : tmp;
    }
    cout << sum << endl;
    return 0;
}