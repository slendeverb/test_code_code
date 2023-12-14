#include <iostream>
using namespace std;

struct Date
{
    int start_month;
    int start_day;
    int first_day_number;
    int end_month;
    int end_day;
} date;

int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int count_day(Date date)
{
    if (date.start_month == date.end_month)
    {
        return date.end_day - date.start_day;
    }
    else
    {
        int ret = 0;
        for (int i = 1; i <= 12; i++)
        {
            if (i == date.start_month)
            {
                ret += days[i - 1] - date.start_day;
            }
            else if (i > date.start_month && i < date.end_month)
            {
                ret += days[i - 1];
            }
            else if (i == date.end_month)
            {
                ret += date.end_day;
                break;
            }
        }
        return ret;
    }
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        cin >> date.start_month >> date.start_day >> date.first_day_number >> date.end_month >> date.end_day;
        int day = count_day(date);
        long ans = date.first_day_number;
        for (int i = 1; i <= day; i++)
        {
            ans *= 2;
        }
        cout << ans << "\n";
    }
    return 0;
}