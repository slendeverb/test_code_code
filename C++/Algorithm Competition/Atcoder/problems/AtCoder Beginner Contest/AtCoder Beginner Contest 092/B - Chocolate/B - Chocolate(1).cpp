#include <iostream>
using namespace std;

int main()
{
    int n = 0, d = 0, x = 0;
    cin >> n >> d >> x;
    int *p = new int[n + 1];
    int count = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int tmp = 0;
        for (int j = 1; j <= d; j = j * tmp + 1)
        {
            j = p[i];
            tmp++;
            count++;
        }
    }
    cout << count + x << endl;
    return 0;
}