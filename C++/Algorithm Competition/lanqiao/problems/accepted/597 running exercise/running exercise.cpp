#include <iostream>
using namespace std;

int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
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
    int kilometres = 0;
    int week_day = 6;

    for (int year = 2000; year <= 2020; year++)
    {
        if (is_leap_year(year))
        {
            days[1] = 29;
        }
        else
        {
            days[1] = 28;
        }

        for (int month = 1; month <= 12; month++)
        {
            for (int day = 1; day <= days[month - 1]; day++)
            {
                kilometres++;

                if (week_day > 7)
                {
                    week_day = 1;
                }

                if (week_day == 1 || day == 1)
                {
                    kilometres++;
                }

                week_day++;

                if (year == 2020 && month == 10 && day == 1)
                {
                    goto End;
                }
            }
        }
    }

End:
    cout << kilometres << "\n";
    return 0;
}