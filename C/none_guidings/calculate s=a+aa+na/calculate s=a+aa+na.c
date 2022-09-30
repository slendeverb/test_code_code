#include<stdio.h>

int main()
{
	int n = 0;
	int a = 0;
	int i = 0;
	unsigned long long int sum = 0;
	scanf("%d %d", &n, &a);

	for (i = 1; i <= n; i++)
	{
		int j = 0;
		unsigned long long int p = 1;
		unsigned long long int tmp = 0;
		unsigned long long int ret = 0;
		for (j = 1; j <= i; j++)
		{
			tmp = p * a;
			ret += tmp;
			p *= 10;
		}
		sum += ret;
	}

	printf("%lld", sum);

	return 0;
}