#include<stdio.h>

int main()
{
	int a = 0;
	int i = 0;
	int count = 0;
	scanf("%d", &a);
	while (a != 0)
	{
		if ((a & 1) == 1)
		{
			count++;
		}
		a >>= 1;
	}
	printf("%d\n", count);
	getchar();
	getchar();
	return 0;
}