#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    ll n, m, a;
    ll count = 2;
    cin >> n >> m >> a;
    if (a * a >= n * m)
    {
        cout << 1 << endl;
    }
    else
    {
        int i = 2;
        while (1)
        {
            count = i * i;
            if (count * a * a >= n * m)
            {
                cout << count << endl;
                break;
            }
            else
            {
                i++;
            }
        }
    }
    return 0;
}