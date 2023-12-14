#include <iostream>
#include <string>
using namespace std;

string s;

int main()
{
    cin >> s;
    if (s == "Monday")
    {
        cout << 5 << "\n";
    }
    else if (s == "Tuesday")
    {
        cout << 4 << "\n";
    }
    else if (s == "Wednesday")
    {
        cout << 3 << "\n";
    }
    else if (s == "Thursday")
    {
        cout << 2 << "\n";
    }
    else if (s == "Friday")
    {
        cout << 1 << "\n";
    }
    return 0;
}