#include <iostream>
using namespace std;

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int ans = 0;
		while (n)
		{
			ans += n /= 5;
		}
		cout << ans << endl;
	}
	return 0;
}