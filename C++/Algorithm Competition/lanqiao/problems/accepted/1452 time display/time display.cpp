#include <iostream>
using namespace std;

int main()
{
    long long n = 0;
    cin >> n;
    n /= 1000;
    int second = n % 60;
    n /= 60;
    int minute = n % 60;
    n /= 60;
    int hour = n % 24;
    if (hour < 10)
    {
        cout << "0" << hour << ":";
    }
    else
    {
        cout << hour << ":";
    }
    if (minute < 10)
    {
        cout << "0" << minute << ":";
    }
    else
    {
        cout << minute << ":";
    }
    if (second < 10)
    {
        cout << "0" << second << "\n";
    }
    else
    {
        cout << second << "\n";
    }
    return 0;
}