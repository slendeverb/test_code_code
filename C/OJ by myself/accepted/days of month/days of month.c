#include <stdio.h>
int main()
{
	int year = 0, month = 0;
	while (scanf("%d %d", &year, &month) != EOF)
	{
		if (month != 2)
		{
			if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				printf("%d\n", 30);
			}
			else
			{
				printf("%d\n", 31);
			}
		}
		else
		{
			if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
			{
				printf("%d\n", 29);
			}
			else
			{
				printf("%d\n", 28);
			}
		}
	}
	return 0;
}