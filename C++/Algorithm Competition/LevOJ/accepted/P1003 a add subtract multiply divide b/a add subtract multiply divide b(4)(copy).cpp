#include <stdio.h>
#include <math.h>

int main(void) {
	char trash;
	unsigned n, a, b;
	char ops;
	trash = scanf("%d%c", &n, &trash);
	for (; n > 0; --n) {
		trash = scanf("%d%c%d%c", &a, &ops, &b, &trash);
		switch (ops)
		{
		case '+':
			printf("%llu\n", (unsigned long long)a + (unsigned long long)b); break;
		case '-':
			if (a>b) {
				printf("%u\n", a - b);
			}
			else if (a<b)  {
				printf("-%u\n", b - a);
			}
			else {
				printf("0\n");
			}
			; break;
		case '*':
			printf("%.0lf\n", (double)a * (double)b); break;
		case '/':
			printf("%u\n", a / b);
		default:
			break;
		}
	}
	return 0;
}
