#include <stdio.h>
#include <math.h>
int main()
{
	int n = 0;
	scanf("%d", &n);
	while (n--)
	{
		unsigned long int a = 0;
		scanf("%lu", &a);
		int i = 0;
		unsigned long int b = 0;
		unsigned long int c = a;
		int t = 0;
		while (c)
		{
			t = c % 10;
			b = b * 10 + t;
			c /= 10;
		}
		unsigned long int max = a > b ? a : b;
		int flag = 1;
		for (i = 2; i <= sqrt(max); i++)
		{
			if (a % i == 0 || b % i == 0)
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			printf("%d\n", 1);
		}
		else
		{
			printf("%d\n", 0);
		}
	}
	return 0;
}