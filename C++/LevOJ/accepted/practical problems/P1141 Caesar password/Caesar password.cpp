#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string Start, End;
string password;

int main()
{
    while (getline(cin, Start))
    {
        if (Start != "START")
        {
            break;
        }
        getline(cin, password);
        for (int i = 0; i < password.size(); i++)
        {
            if (isupper(password[i]))
            {
                password[i] -= 5;
                if (!isupper(password[i]))
                {
                    password[i] += 26;
                }
            }
        }
        cout << password << "\n";
        getline(cin, End);
    }
    return 0;
}