#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s = "13811111111";
    string sub = "6" + s.substr(s.size() - 5, 5);
    cout << sub << "\n";
    return 0;
}