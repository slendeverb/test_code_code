#include <stdio.h>
int main()
{
	unsigned int a, b;
	char ch;
	while (scanf("%d%c%d", &a, &ch, &b) != EOF)
	{
		if (ch == '+')
		{
			printf("%d\n", a + b);
		}
		if (ch == '-')
		{
			printf("%d\n", a - b);
		}
		if (ch == '*')
		{
			printf("%d\n", a * b);
		}
		if (ch == '/')
		{
			printf("%d\n", a / b);
		}
	}
	return 0;
}