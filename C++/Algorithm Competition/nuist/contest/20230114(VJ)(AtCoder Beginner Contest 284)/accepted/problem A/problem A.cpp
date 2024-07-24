#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> v;
string s;

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        v.push_back(s);
    }
    for (int i = n - 1; i >= 0; i--)
    {
        cout << v[i] << "\n";
    }
    return 0;
}