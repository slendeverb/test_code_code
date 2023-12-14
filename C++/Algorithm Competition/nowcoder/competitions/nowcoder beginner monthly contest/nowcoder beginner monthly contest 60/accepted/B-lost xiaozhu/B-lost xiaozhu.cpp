#include <iostream>
using namespace std;
int arr[100000];
int p[100000];
int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        p[arr[i]]++;
    }
    for (int i = 0; i < q; i++)
    {
        int x = 0;
        cin >> x;
        cout << n - p[x] << endl;
    }
    return 0;
}