#include <iostream>
using namespace std;

int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int days_leap[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int x)
{
    if (x % 4 == 0 && x % 100 != 0 || x % 400 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int a[8];
int flag1 = 1;

bool check1(int year, int month, int day)
{
    int year_num = 4;
    while (year)
    {
        int tmp = year % 10;
        a[--year_num] = tmp;
        year /= 10;
    }
    if (month < 10)
    {
        a[4] = 0;
        a[5] = month;
    }
    else
    {
        a[5] = month % 10;
        a[4] = month / 10;
    }
    if (day < 10)
    {
        a[6] = 0;
        a[7] = day;
    }
    else
    {
        a[7] = day % 10;
        a[6] = day / 10;
    }

    int flag = 1;

    for (int i = 0; i <= 3; i++)
    {
        if (a[i] != a[7 - i])
        {
            flag = 0;
            break;
        }
    }

    if (flag)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check2()
{
    if (a[0] == a[2] && a[0] == a[5] && a[0] == a[7] && a[1] == a[3] && a[1] == a[4] && a[1] == a[6])
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int year, month, day;
    scanf("%4d%2d%2d", &year, &month, &day);
    for (int i = year; i <= 9999; i++)
    {
        for (int j = 1; j <= 12; j++)
        {
            int tmp = is_leap_year(i) ? days_leap[j - 1] : days[j - 1];
            for (int k = 1; k <= tmp; k++)
            {
                if (check1(i, j, k))
                {
                    if (flag1)
                    {
                        for (int i = 0; i <= 7; i++)
                        {
                            cout << a[i];
                        }
                        cout << "\n";
                        flag1 = 0;
                    }

                    if (check2())
                    {
                        for (int i = 0; i <= 7; i++)
                        {
                            cout << a[i];
                        }
                        cout << '\n';

                        goto End;
                    }
                }
            }
        }
    }
End:
    return 0;
}