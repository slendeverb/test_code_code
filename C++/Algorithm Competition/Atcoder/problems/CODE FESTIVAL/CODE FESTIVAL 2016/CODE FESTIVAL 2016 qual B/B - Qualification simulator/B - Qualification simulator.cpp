#include <iostream>
using namespace std;
#include <string>

int main()
{
    int n = 0;
    int a = 0, b = 0;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    int count = 0;
    int count_overseas = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'c')
        {
            cout << "No" << endl;
            continue;
        }
        else if (s[i] == 'a')
        {
            if (count < a + b)
            {
                cout << "Yes" << endl;
                count++;
            }
            else
            {
                cout << "No" << endl;
            }
        }
        else if (s[i] == 'b')
        {
            if (count < a + b && count_overseas < b)
            {
                cout << "Yes" << endl;
                count++;
                count_overseas++;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}