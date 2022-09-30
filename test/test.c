#include<stdio.h>

int main()
{
	unsigned int a = 0;
	unsigned int b = 0;
	int num = 0;
	int i = 0;
	int j = 0;
	scanf("%d", &num);
	unsigned int arr[20] = { 0 };
	char ch[10] = { 0 };
	for (i = 0; i < num; i++)
	{
		scanf("%u%c%u", &arr[j], &ch[i], &arr[j + 1]);
		j += 2;
	}
	j = 0;
	for (i = 0; i < num; i++)
	{
		a = arr[j];
		b = arr[j + 1];
		switch (ch[i])
		{
		case '+':
			printf("%d\n", a + b);
			break;
		case '-':
			printf("%d\n", a - b);
			break;
		case '*':
			printf("%d\n", a * b);
			break;
		case '/':
			printf("%d\n", a / b);
			break;
		}
		j += 2;
	}
	return 0;
}