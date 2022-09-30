#include<stdio.h>
//#include<math.h>

int main()
{
	int n = 0;
	int a = 0;
	int i = 0;
	int sum = 0;
	
	scanf("%d %d", &n, &a);
	printf("sum=%d", a);
	for (i = 2; i <= n; i++)
	{
		int j = 0;
		unsigned long long int ret = 0;
		unsigned long long int p = 1;
		for (j = 0; j < i; j++)
		{
			unsigned long long int tmp = 0;
			tmp = a * p;//或者pow(10,j)
			p *= 10;
			ret += tmp;
		}
		printf("+%lld", ret);
	}
	return 0;
}