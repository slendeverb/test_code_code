#include <iostream>
using namespace std;
#include <string.h>

void reverse(char *left, char *right)
{
    while (left < right)
    {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}
int main()
{
    int t = 0;
    cin >> t;
    while (t--)
    {
        int count = 0;
        char s[6] = {0};
        scanf("%5s", s);
        s[0] = s[1] = '0';
        char s1[6] = {0};
        int x = 0;
        cin >> x;
        int x1 = x;
        if (strcmp(s, "00:00") == 0 && x == 1)
        {
            cout << 16 << endl;
            continue;
        }
        while (strcmp(s, "2400") < 0)
        {
            if (x1 / 60 == 0)
            {
                s[4] += x % 10;
                while (s[4] > '9')
                {
                    s[4] = (s[4] - '0') % 10 + '0';
                    s[3] += 1;
                }
                x /= 10;
                s[3] += x;
                while (s[3] > '5')
                {
                    s[3] = (s[3] - '0') % 6 + '0';
                    s[1] += 1;
                }
                while (s[0] < '2' && s[1] > '9')
                {
                    s[1] = (s[1] - '0') % 10 + '0';
                    s[0] += 1;
                }
                while (s[0] == '2' && s[1] > '3')
                {
                    s[1] = (s[1] - '3') % 4 + '0';
                    s[0] = '0';
                }
            }
            else if (x1 % 60 == 0)
            {
                s[1] += x1 / 60;
                while (s[1] > '9')
                {
                    s[1] = (s[1] - '0') % 10 + '0';
                    s[0] += 1;
                }
                while (s[0] == '2' && s[1] > '3')
                {
                    s[1] = (s[1] - '3') % 4 + '0';
                    s[0] = '0';
                }
            }
            else
            {
                int x2 = x1 % 60;
                s[4] += x2 % 10;
                while (s[4] > '9')
                {
                    s[4] = (s[4] - '0') % 10 + '0';
                    s[3] += 1;
                }
                x2 /= 10;
                s[3] += x2;
                while (s[3] > '5')
                {
                    s[3] = (s[3] - '0') % 6 + '0';
                    s[1] += 1;
                }
                int x3 = x1 / 60;
                s[1] += x3;
                while (s[0] < '2' && s[1] > '9')
                {
                    s[1] = (s[1] - '0') % 10 + '0';
                    s[0] += 1;
                }
                while (s[0] == '2' && s[1] > '3')
                {
                    s[1] = (s[1] - '3') % 4 + '0';
                    s[0] = '0';
                }
            }
            for (int i = 0; i < 5; i++)
            {
                s1[i] = s[i];
            }
            reverse(s1 + 0, s1 + 4);
            if ((strcmp(s, s1)) == 0)
            {
                count++;
            }
        }
        cout << count << endl;
    }
    return 0;
}