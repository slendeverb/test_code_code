#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> v;
string s;

int main()
{
    int count = 0;

    for (int i = 0; i < 30; i++)
    {
        cin >> s;
        v.push_back(s);
    }

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            for (int x = 0; x < 30; x++)
            {
                for (int y = 0; y < 50; y++)
                {
                    if (v[i][j] < v[x][y] && ((i == x && j < y) || (i < x && j == y) || abs(x - i) == abs(y - j)) && !(x <= i && y <= j))
                    {
                        count++;
                    }
                }
            }
        }
    }

    cout << count << "\n";
    return 0;
}