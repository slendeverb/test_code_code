#include <stdio.h>
int main()
{
	int a = 0;
	while (scanf("%d", &a) != EOF)
	{
		int b = 0, c = a, tmp = 0;
		while (c)
		{
			tmp = c % 10;
			b = b * 10 + tmp;
			c /= 10;
		}
		if (a == b)
		{
			printf("%s\n", "yes");
		}
		else
		{
			printf("%s\n", "no");
		}
	}
	return 0;
}