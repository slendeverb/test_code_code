#include <iostream>
using namespace std;

int main()
{
    int k = 0, n = 0;
    cin >> k >> n;
    int *arr = new int[n];
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if (i >= 1)
        {
            ans = max(ans, arr[i] - arr[i - 1]); //计算中间房子距离的最大值
        }
    }
    ans = max(ans, (k + arr[0]) - arr[n - 1]); //计算第一个房子和最后一个房子之间的距离
    cout << k - ans << endl;                   //减去最大的距离，就是走的最小的距离
    return 0;
}