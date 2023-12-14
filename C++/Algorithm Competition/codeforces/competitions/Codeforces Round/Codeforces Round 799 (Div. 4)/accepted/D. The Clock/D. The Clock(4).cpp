#include <iostream>
#include <set>
#include <string>
using namespace std;

int hour_to_minute[5] = {600, 60, 0, 10, 1};
int palindrome_minutes[16] = {0, 70, 140, 210, 280, 350, 601, 671, 741, 811, 881, 951, 1202, 1272, 1342, 1412};

int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        int x = 0;
        cin >> x;
        set<int> t;
        int time_minutes = 0;
        for (int i = 0; i < 5; i++)
        {
            time_minutes += (s[i] - '0') * hour_to_minute[i];
        }
        for (int i = 0; i < 1440; i++)
        {
            t.insert(time_minutes);
            time_minutes += x;
            time_minutes %= 1440;
        }
        int ret = 0;
        for (int i : t)
        {
            for (int j = 0; j < 16; j++)
            {
                if (palindrome_minutes[j] == i)
                {
                    ret++;
                }
            }
        }
        cout << ret << endl;
    }
    return 0;
}