#include <iostream>
using namespace std;

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int Takahashi = (a * 3600 + b * 60) % (24 * 3600);
    int Aoki = (c * 3600 + d * 60 + 1) % (24 * 3600);
    if (Takahashi < Aoki)
    {
        cout << "Takahashi\n";
    }
    else
    {
        cout << "Aoki\n";
    }
    return 0;
}