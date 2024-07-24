#include <iostream>
using namespace std;
#include <vector>
#include <map>

int main()
{
    int a[3][3] = {0};
    bool a1[5][5] = {false};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> a[i][j];
        }
    }
    int n = 0;
    cin >> n;
    vector<int> b(n + 1, 0);
    map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        mp[b[i]]++;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (mp[a[i][j]] != 0)
            {
                a1[i + 1][j + 1] = true;
            }
        }
    }
    int flag = 0;
    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            if (a1[i][j] == true && a1[i][j - 1] == a1[i][j] && a1[i][j] == a1[i][j + 1])
            {
                flag = 1;
            }
            else if (a1[i][j] == true && a1[i - 1][j] == a1[i][j] && a1[i][j] == a1[i + 1][j])
            {
                flag = 1;
            }
            else if (a1[i][j] == true && a1[i - 1][j - 1] == a1[i][j] && a1[i][j] == a1[i + 1][j + 1])
            {
                flag = 1;
            }
            else if (a1[i][j] == true && a1[i - 1][j + 1] == a1[i][j] && a1[i][j] == a1[i + 1][j - 1])
            {
                flag = 1;
            }
        }
    }
    if (flag)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}