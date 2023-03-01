#include <stdio.h>

int gcd(int a, int b)
{
	int t;
	while (t = a % b)
	{
		a = b;
		b = t;
	}
	return b;
}

int main()
{
	int n, a, b;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d %d", &a, &b);
		printf("%d\n", gcd(a, b));
	}
	return 0;
}