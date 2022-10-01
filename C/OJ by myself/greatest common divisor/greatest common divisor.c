#include <stdio.h>
int main()
{
	int n = 0;
	int i = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		int a = 0;
		int b = 0;
		scanf("%d %d", &a, &b);
		int max = a < b ? a : b;
		while (1)
		{
			if (a % max == 0 && b % max == 0)
			{
				printf("%d\n", max);
				break;
			}
			max--;
		}
	}
	return 0;
}