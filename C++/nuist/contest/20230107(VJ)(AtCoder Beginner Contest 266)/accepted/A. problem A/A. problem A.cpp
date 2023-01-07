#include <iostream>
#include <string>
using namespace std;

string s;

int main()
{
    cin >> s;
    cout << s[(s.size() + 1) / 2 - 1] << "\n";
    return 0;
}