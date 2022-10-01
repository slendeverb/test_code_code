#include <stdio.h>
int main()
{
	int n = 0;
	int i = 0;
	while (scanf("%d", &n) != EOF)
	{
		int count = 0;
		for (i = 1; i <= n; i++)
		{
			if (i % 5 == 0)
			{
				count++;
			}
			if (i % 25 == 0)
			{
				count++;
			}
		}
		printf("%d\n", count);
	}
	return 0;
}