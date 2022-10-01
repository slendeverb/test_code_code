#include <stdio.h>
#include <math.h>
int main()
{
	int a = 0, b = 0, c = 0;
	while (scanf("%d %d %d", &a, &b, &c) != EOF)
	{
		double area = 0;
		double p = (a + b + c) / 2.0;
		if (a + b > c && a + c > b && b + c > a)
		{
			area = sqrt(p * (p - a) * (p - b) * (p - c));
			printf("%.2lf\n", area);
		}
		else
		{
			printf("%d\n", -1);
		}
	}
	return 0;
}