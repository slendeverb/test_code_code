#include <iostream>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int a = 0, b = 0, c = 0, d = 0;
        cin >> a >> b >> c >> d;
        int count = 0;
        if (b > a)
        {
            count++;
        }
        if (c > a)
        {
            count++;
        }
        if (d > a)
        {
            count++;
        }
        cout << count << endl;
    }
    return 0;
}